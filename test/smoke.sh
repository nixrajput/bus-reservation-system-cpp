#!/bin/sh
# Drives the app with scripted input. Usage: smoke.sh <path-to-binary>
set -eu

bin=$1
work=$(mktemp -d)
trap 'rm -rf "$work"' EXIT
mkdir "$work/run" "$work/data"
cd "$work/run" # the app reads and writes ../data

fail() {
    echo "FAIL: $1"
    exit 1
}

run() {
    timeout 20 "$bin" >"$work/out.txt" 2>/dev/null || fail "$1 (exit $?)"
}

count() {
    grep -c "$1" "$work/out.txt" || true
}

# Prints text padded with NUL bytes to a fixed width: field <text> <width>
field() {
    printf '%s' "$1"
    head -c $(($2 - ${#1})) /dev/zero
}

# Prints one ticket in the 1.1.x layout (10-byte PNR field), little-endian, 168 bytes.
old_ticket() {
    field Dana 20
    field PNR12345 10
    field 5-11-2025 20
    head -c 6 /dev/zero                         # padding before the Bus
    printf '\040\000\000\000\001\000\000\000' # maxSeats 32, bookedSeats 1
    printf '\000\000\000\000\000\000\131\100' # busFare 100.0
    field B1 10
    field A 20
    field B 20
    field 9 20
    field 10 20
    head -c 6 /dev/zero # padding after the Bus
}

# Non-numeric menu input and end of input must exit, not loop forever.
run "non-numeric input or end of input" <<'EOF'
x
2
EOF
[ ! -e ../data/admin.dat ] || fail "an unfinished password setup created admin.dat"

# The first admin login sets a password. Bad fares are rejected, and an edited fare keeps every digit.
run "admin session" <<'EOF'
2
short
short
2
longpassword1
different123
2
correct horse battery
correct horse battery
1
B1
A
B
9
10
-5
1
B1
A
B
9
10
abc
1
B1
A
B
9
10
100
8
B1




250
8
B1




-5
2
6
7
10
3
EOF
[ "$(count 'Passwords must match')" = 2 ] || fail "a short or mismatched password was accepted"
[ "$(count 'Invalid Bus Fare\.\.\.')" = 2 ] || fail "bad fares were not rejected"
[ "$(count 'keeping the old fare')" = 1 ] || fail "a rejected edit fare was not reported"
[ "$(count 'VIEW BOOKINGS')" = 1 ] || fail "bookings menu did not open"
[ "$(count 'ADMIN PORTAL')" = 8 ] || fail "BACK did not return to the admin menu"
# One fare line per edit screen (2) plus one per listed bus (1).
[ "$(count 'Bus Fare:-> [0-9]')" = 3 ] || fail "expected exactly one saved bus"
[ "$(count 'Bus Fare:-> 250.00')" = 2 ] || fail "edited fare was not saved as 250.00"

# admin.dat is owner-only and holds a salted hash, never the password.
[ -n "$(find ../data/admin.dat -perm 600)" ] || fail "admin.dat is not owner-only (0600)"
! grep -q 'correct horse' ../data/admin.dat || fail "admin.dat holds the plain password"
read -r salt hash <../data/admin.dat
expected=$(python3 -c '
import hashlib, sys
h = hashlib.sha256((sys.argv[1] + sys.argv[2]).encode()).digest()
for _ in range(99999):
    h = hashlib.sha256(h).digest()
print(h.hex())' "$salt" 'correct horse battery')
[ "$expected" = "$hash" ] || fail "admin.dat hash is not 100000 rounds of salted SHA-256"

# A later login needs the saved password; a wrong one returns to the main menu.
run "admin login" <<'EOF'
2
wrong password
2
correct horse battery
10
3
EOF
[ "$(count 'Wrong Password')" = 1 ] || fail "a wrong password was not rejected"
[ "$(count 'ADMIN PORTAL')" = 1 ] || fail "the saved password did not log in"

# A failed cancel must not leave a temp file that a later booking appends to.
size=$(wc -c <../data/buses.dat)
run "user session" <<'EOF'
1
1
A
B
B1
Alice
3
NOPE
1
A
B
B1
Bob
4
3
EOF
[ "$(count 'Ticket Booked Successfully')" = 2 ] || fail "expected two bookings"
# Both bookings happen within a second; time-seeded PNRs used to collide here.
pnrs=$(grep -o 'PNR No:-> [A-Z0-9]*' "$work/out.txt" | sed 's/.*-> //')
[ "$(echo "$pnrs" | grep -cE '^[A-Z0-9]{10}$')" = 2 ] || fail "PNRs are not 10 letters or digits"
[ "$(echo "$pnrs" | sort -u | wc -l | tr -d ' ')" = 2 ] || fail "two bookings got the same PNR"
[ "$(wc -c <../data/buses.dat)" = "$size" ] || fail "buses.dat changed size, records were corrupted"

# If a temp file cannot be written, nothing is saved and the app says so.
pnr=$(echo "$pnrs" | head -n 1)
cp ../data/buses.dat "$work/buses.before"
cp ../data/reservations.dat "$work/reservations.before"
mkdir -p ../data/temp.dat/blocked # a non-empty directory cannot be opened, removed or renamed over
run "unwritable temp file" <<EOF
1
1
A
B
B1
Carol
3
$pnr
4
3
EOF
rm -r ../data/temp.dat
[ "$(count "Can't Save Changes")" = 2 ] || fail "failed saves were not reported"
cmp -s ../data/buses.dat "$work/buses.before" || fail "buses.dat changed after a failed save"
cmp -s ../data/reservations.dat "$work/reservations.before" || fail "reservations.dat changed after a failed save"

# A new bus starts with no booked seats, even after the menu read a bus that has some (B1 has 2).
run "add a bus after viewing buses" <<'EOF'
2
correct horse battery
2
1
B2
A
C
9
10
100
7
B2
10
3
EOF
[ "$(count 'Seats Remaining:-> 32')" = 1 ] || fail "a new bus started with booked seats"
[ "$(count 'Seats Remaining:-> 30')" = 1 ] || fail "B1 should have 2 booked seats"

# Cancelling a ticket on a bus with 0 booked seats keeps the count at 0 and reports the mismatch.
run "cancel on a bus with no booked seats" <<EOF
2
correct horse battery
9
B1
1
B1
A
B
9
10
100
10
1
3
$pnr
4
2
correct horse battery
7
B1
10
3
EOF
[ "$(count 'had no booked seats to free')" = 1 ] || fail "a seat count mismatch was not reported"
[ "$(count 'Reservation Cancelled\.\.\.')" = 0 ] || fail "a seat count mismatch was reported as a clean cancel"
[ "$(count 'Seats Remaining:-> 32')" = 1 ] || fail "a cancel drove the booked seats below 0"

# A reservations.dat saved by 1.1.x is upgraded once, with a backup, and keeps every field.
mkdir "$work/m" "$work/m/run" "$work/m/data"
cd "$work/m/run"
old_ticket >../data/reservations.dat
cp ../data/reservations.dat "$work/m/original.dat"
run "upgrade old tickets" <<'EOF'
1
2
PNR12345
4
3
EOF
[ "$(count 'Upgraded data/reservations.dat')" = 1 ] || fail "old tickets were not upgraded"
for want in 'Name:-> Dana' 'PNR No:-> PNR12345' 'Bus No:-> B1' 'Seat No.:-> 1' 'Date:-> 5-11-2025' 'From:-> A' 'Bus Fare:-> 100.00'; do
    [ "$(count "$want")" = 1 ] || fail "the upgraded ticket lost '$want'"
done
cmp -s ../data/reservations.dat.bak "$work/m/original.dat" || fail "reservations.dat.bak is not the original file"

run "start after the upgrade" <<'EOF'
1
2
PNR12345
4
3
EOF
[ "$(count 'Upgraded')" = 0 ] || fail "an upgraded file was upgraded again"
[ "$(count 'Date:-> 5-11-2025')" = 1 ] || fail "the second start changed the upgraded ticket"

# If the upgrade cannot write its temp file, the app stops and leaves the original file unchanged.
old_ticket >../data/reservations.dat
mkdir -p ../data/temp.dat/blocked
status=0
timeout 20 "$bin" </dev/null >"$work/out.txt" 2>/dev/null || status=$?
rm -r ../data/temp.dat
[ "$status" = 1 ] || fail "a failed upgrade should exit 1, got $status"
[ "$(count "Can't upgrade data/reservations.dat")" = 1 ] || fail "a failed upgrade was not reported"
cmp -s ../data/reservations.dat "$work/m/original.dat" || fail "a failed upgrade changed reservations.dat"

echo "smoke: all checks passed"
