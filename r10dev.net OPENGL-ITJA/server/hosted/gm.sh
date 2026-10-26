#!/usr/bin/env bash
# Safely grant or update a GM authority for an existing character.
# Usage: docker compose exec m2 /app/gm.sh <account-login> <character-name> [authority]
set -euo pipefail
if [ "$#" -lt 2 ] || [ "$#" -gt 3 ]; then
  echo "usage: gm.sh <login> <character> [IMPLEMENTOR|HIGH_WIZARD|GOD|LOW_WIZARD|PLAYER]" >&2
  exit 2
fi
login="$1"
character="$2"
authority="${3:-IMPLEMENTOR}"
case "$authority" in
  IMPLEMENTOR|HIGH_WIZARD|GOD|LOW_WIZARD|PLAYER) ;;
  *) echo "invalid GM authority: $authority" >&2; exit 2 ;;
esac
db="${M2_DATA:-/data}/sqlite/common.sqlite3"
if [ ! -f "$db" ]; then
  echo "GM database not found: $db" >&2
  exit 1
fi
# SQL string literals are escaped by doubling quotes. Do not interpolate raw values.
escape_sql() { printf '%s' "$1" | sed "s/'/''/g"; }
login_sql="$(escape_sql "$login")"
character_sql="$(escape_sql "$character")"
authority_sql="$(escape_sql "$authority")"
sqlite3 -bail "$db" <<SQL
BEGIN IMMEDIATE;
DELETE FROM gmlist WHERE mAccount = '$login_sql' AND mName = '$character_sql';
INSERT INTO gmlist (mAccount,mName,mAuthority)
VALUES ('$login_sql','$character_sql','$authority_sql');
COMMIT;
SQL
echo "GM authority '$authority' assigned to '$character' (account '$login'); relog to apply."
