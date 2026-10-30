# Drakon2 — branding and rollout

**Chosen brand:** Drakon2
**Region:** Romania
**Game direction:** Oldschool modernizat, Android-first
**Admin:** server-side OWNER / ADMIN / GM / HELPER roles

## Brand rollout rules

1. Keep the existing `metin2-mobile` repository and Android package ID for upgrade compatibility until a separately tested rebrand migration exists.
2. Rename only our own UI, server list labels, docs and admin branding. Do not rename or remove third-party copyright notices.
3. Keep the existing Single Player entry and development server entry unchanged until a reachable Drakon2 realm has passed two-device tests.
4. A production catalog entry should be named `Drakon2 Romania`, with actual verified host/ports; never insert dummy IPs.
5. Do not imply the game is officially affiliated with Metin2, Webzen or Gameforge. Commercial public launch requires licensing review and original or properly licensed assets.
6. The GM authorization namespace in this feature branch is `drakon2`; actual server integration remains outstanding.

## Definition of first playable online milestone

- Two distinct Android clients can connect to the same persistent realm.
- Both can see each other move, fight, disconnect and reconnect.
- A normal player cannot invoke a GM command.
- An authorized GM can invoke a read-only command and its audit entry is recorded.
- Single Player remains functional.
