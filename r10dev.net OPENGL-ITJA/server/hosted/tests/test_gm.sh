#!/usr/bin/env bash
# Integration test for hosted GM role assignment; requires sqlite3 and bash.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
gm="$script_dir/../gm.sh"
tmp="$(mktemp -d)"
trap 'rm -rf "$tmp"' EXIT
mkdir -p "$tmp/sqlite"
db="$tmp/sqlite/common.sqlite3"
sqlite3 "$db" 'CREATE TABLE gmlist (mAccount TEXT, mName TEXT, mAuthority TEXT);'
export M2_DATA="$tmp"

bash "$gm" test Nistor IMPLEMENTOR
[ "$(sqlite3 "$db" "SELECT mAuthority FROM gmlist WHERE mName='Nistor'")" = IMPLEMENTOR ]

# Updating an existing GM must not create duplicate rows.
bash "$gm" test Nistor GOD
[ "$(sqlite3 "$db" "SELECT count(*) FROM gmlist WHERE mName='Nistor'")" = 1 ]
[ "$(sqlite3 "$db" "SELECT mAuthority FROM gmlist WHERE mName='Nistor'")" = GOD ]

# Quotes in character names must not allow SQL injection.
bash "$gm" test "Nistor'GM" LOW_WIZARD
[ "$(sqlite3 "$db" "SELECT count(*) FROM gmlist")" = 2 ]
[ "$(sqlite3 "$db" "SELECT mAuthority FROM gmlist WHERE mName='Nistor''GM'")" = LOW_WIZARD ]

# Reject unknown authority without changing the database.
if bash "$gm" test Nistor ROOT >/dev/null 2>&1; then
  echo 'Invalid authority was accepted' >&2
  exit 1
fi
[ "$(sqlite3 "$db" "SELECT mAuthority FROM gmlist WHERE mName='Nistor'")" = GOD ]
echo 'GM role tests passed'
