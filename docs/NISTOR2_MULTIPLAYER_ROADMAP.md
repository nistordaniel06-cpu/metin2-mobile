# Drakon2 România — Multiplayer Foundation

This branch prepares the existing Android client and compatible m2dev server for a persistent Romanian Oldschool-modernized realm. **No existing offline gameplay or production catalog entries are modified.**

## Verified baseline

- Android client supports embedded Single Player and remote server selection.
- Remote server catalog: `r10dev.net OPENGL-ITJA/android/servers/servers.json`.
- Compatible server source revision: `d1str4ught/m2dev-server-src@66068c1`.
- Compatible server runtime revision: `d1str4ught/m2dev-server@ad30738`.
- Newer server handshake is incompatible with this client without a protocol port.
- A remote server must expose auth and every advertised game-core port; DB and P2P ports remain private.

## Phase 1: first two-player test

1. Provision a Linux VM (Ubuntu 22.04 baseline) with a private MariaDB instance, firewall, and SSH key access.
2. Follow `docs/SELF_HOSTING.md` to build the **pinned** server and apply `server/m2dev-server-src-linux.patch`.
3. Replace all default SQL account passwords and database credentials; bind database and internal P2P ports to private interfaces only.
4. Start auth and channel cores. Confirm `PUBLIC_IP` and redirects advertise an address reachable from both Android devices.
5. Add a **new** remote server entry in the catalog only after the endpoint is deployed, checked, and has a stable DNS name. Bump catalog version.
6. Test two distinct accounts on two phones: login, same map, visible movement, combat, reconnect, and persisted inventory.
7. Capture server logs and Android crash logs; resolve issues before any public release.

## Proposed realm settings (not yet enabled)

- Name: Drakon2 Romania
- Style: Oldschool modernized; PvM and PvP
- Initial level cap target: 120 (subject to data and balancing)
- XP target: x3 (requires server configuration)
- Launch channels: one initially; scale after load testing
- Monetization: cosmetic-first, no pay-to-win power

## Acceptance criteria

- [ ] Two phones connect to the same remote channel concurrently.
- [ ] Movement is visible to both clients.
- [ ] Server validates attack range and damage.
- [ ] Inventory, XP and position persist after disconnect.
- [ ] Single Player remains playable without network.
- [ ] No credentials or licensed game assets are committed.
- [ ] No public realm is advertised until legal/licensing review and security checks are complete.

## Next implementation boundary

The current repository provides the game client, server patches and instructions; it does **not** provision or run a persistent remote host. Do not claim that this branch enables live multiplayer without a deployed server and a two-device integration test.
