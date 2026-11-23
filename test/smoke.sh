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

echo "smoke: all checks passed"
