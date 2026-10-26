# Metin2 Nistor V2 — Implementation plan

Status: planning branch, **not a playable V2 APK**.

## Baseline and safeguards
- Preserve the working Android Single Player mode, joystick, NPC interaction and attack controls.
- Back up existing local save data before installing a new build.
- Identify build dependencies and proprietary game data. Never commit or redistribute proprietary game assets.
- Build and smoke-test on arm64 physical Android before release.

## V2.1 — Combat and progression
- Inspect current server-side combat, mob AI, XP and drop implementations before editing.
- Add or repair authoritative mob aggro, HP, damage, death, respawn, XP and drops as needed.
- Tests: kill mob, receive XP and item, restart app, confirm saved progress.

## V2.2 — Inventory and economy
- Confirm equipment persistence, stackable consumables, Yang and NPC shops.
- Add server-side validation to prevent duplicated items and negative balances.
- Tests: buy, sell, equip, restart, and verify inventory state.

## V2.3 — Game Master
- Add an explicit server-side GM role to a dedicated test account.
- Restrict /level, /item, /spawn, /teleport and /heal to authenticated GM sessions.
- Log every privileged action; reject commands from ordinary players.
- Never implement a client-side-only admin unlock.

## V2.4 and later
- Quests, Metin stones, boss encounters, optional remote multiplayer.

## Release checklist
- [ ] Baseline build passes
- [ ] Existing Android gameplay unaffected
- [ ] Save migration/backup verified
- [ ] Combat and economy tested
- [ ] GM permission tests pass
- [ ] Installable arm64 APK artifact produced
- [ ] Tested on Honor Android device

Changes should be implemented in separate commits and reviewed in a PR before merging to main.
