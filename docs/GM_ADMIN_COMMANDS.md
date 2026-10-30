# Drakon2 — GM / Admin commands (implementation specification)

Status: **planned, not enabled in the Android client or live game server**.

The compatible m2dev server source is an external pinned dependency (`d1str4ught/m2dev-server-src@66068c1`). Implement handlers in that server's existing command dispatcher after inspecting its GM permission checks. Do **not** implement admin powers solely in the Android client.

## Permission model

| Role | Allowed |
|---|---|
| PLAYER | No GM commands |
| HELPER | /gmhelp, /where, /who (read-only) |
| GM | HELPER + /goto, /bring (consent/authorized moderation), /notice, /kick |
| ADMIN | GM + /spawn, /killmob, /item, /setlevel, /setyang, /ban, /unban, /event |
| OWNER | ADMIN + /shutdown (two-step confirmation), /grantgm (out-of-band admin console only) |

Roles must be derived from the authenticated server-side account and checked **on every request**. Never trust a role, player ID or privilege bit supplied by the client. Protect role assignments with a separate administrative interface, MFA and an audit trail. The owner's account should be distinct from their everyday player account.

## Proposed chat commands

| Command | Example | Intended behavior |
|---|---|---|
| /gmhelp | /gmhelp | Show commands allowed for the current role |
| /where | /where | Show current map and coordinates |
| /who | /who | Online count (avoid exposing private account details) |
| /goto | /goto PlayerName | Teleport GM to a player |
| /bring | /bring PlayerName | Move player to GM for moderation, with restrictions |
| /notice | /notice Event starts in 10 minutes | Broadcast a notice |
| /kick | /kick PlayerName reason | Disconnect player with logged reason |
| /spawn | /spawn 101 1 | Spawn a whitelisted monster ID, capped quantity |
| /killmob | /killmob 101 | Remove nearby NPC monster instances, not players |
| /item | /item 19 1 | Grant a whitelisted item, capped quantity |
| /setlevel | /setlevel PlayerName 50 | Set level within configured cap |
| /setyang | /setyang PlayerName 10000 | Set balance within safe bounds, logged |
| /ban | /ban PlayerName 60 reason | Temporary ban in minutes |
| /unban | /unban PlayerName | Remove a ban |
| /event | /event metin_rain start | Start a configured event |
| /shutdown | /shutdown prepare | Prepare server shutdown; confirm via protected console |

IDs above are illustrative and must be validated against the deployed server data.

## Safety requirements

1. Normalize input, reject malformed or oversized arguments, and cap quantities, coordinates, levels and text length.
2. Log actor account ID, target ID, command, parameters, timestamp, outcome, and reason to a protected audit sink.
3. Rate-limit every command, especially /spawn, /item, /notice and /bring.
4. Do not allow spawning in safe zones, on other players or outside map bounds.
5. For /item and /setyang, require a reason and use database transactions; prohibit granting tradable currency/items on a production realm unless explicitly authorized and monitored.
6. Prevent GM commands from affecting a higher-ranked account; require separate approval for destructive actions.
7. Verify reconnect, channel transfer and account role revocation do not retain cached elevated permissions.
8. Add server-side unit tests for denied PLAYER calls, allowed GM calls, malformed arguments, quantity limits and audit writes.
9. Mobile chat should send ordinary text; the **server** decides whether a command is valid. An optional GM UI may be added later.

## Implementation order

- [ ] Inspect pinned upstream `cmd.cpp`, GM role storage and command dispatch.
- [ ] Add server-side role checks and protected audit logging.
- [ ] Implement read-only commands (/gmhelp, /where, /who).
- [ ] Implement moderation (/goto, /notice, /kick, /ban) with limits.
- [ ] Implement spawn and economy tools in a development realm first.
- [ ] Run two-account tests (PLAYER and GM) on the remote server.
- [ ] Expose a mobile GM menu only after server authorization passes.

**Do not set GM privileges via hard-coded client usernames or a publicly exposed debug endpoint.**
