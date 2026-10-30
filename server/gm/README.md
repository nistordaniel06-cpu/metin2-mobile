# Drakon2 GM authorization policy — phase 1

This directory contains a **standalone C++ permission gate and assertions**, not a wired game command dispatcher.

Run locally: `g++ -std=c++17 -Wall -Wextra -pedantic server/gm/test_gm_command_policy.cpp -o /tmp/nistor2-gm-test && /tmp/nistor2-gm-test`

The caller must supply the role read from **authenticated server-side state**, never client input. `authorize` only checks whether a command name is permitted; it does not execute commands, check argument semantics, enforce rate limits or write audit logs. The dispatcher MUST do all those things before enabling a command.

Next: inspect the pinned m2dev `cmd.cpp`/GM role implementation and integrate this gate with its existing permission system; add audit, per-command validation and integration tests. Never give production players GM powers through the Android client.
