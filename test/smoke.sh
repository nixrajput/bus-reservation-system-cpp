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

# Bad fares are rejected, and an edited fare keeps every digit.
run "admin session" <<'EOF'
2
admin
pass
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
2
6
7
10
3
EOF
[ "$(count 'Invalid Bus Fare')" = 2 ] || fail "bad fares were not rejected"
[ "$(count 'VIEW BOOKINGS')" = 1 ] || fail "bookings menu did not open"
[ "$(count 'ADMIN PORTAL')" = 7 ] || fail "BACK did not return to the admin menu"
[ "$(count 'Bus Fare:-> [0-9]')" = 2 ] || fail "expected exactly one saved bus"
[ "$(count 'Bus Fare:-> 250.00')" = 1 ] || fail "edited fare was not saved as 250.00"

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
[ "$(wc -c <../data/buses.dat)" = "$size" ] || fail "buses.dat changed size, records were corrupted"

echo "smoke: all checks passed"
