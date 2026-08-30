# DearModdingUI client contract (vendored)

`API.h` and `ImGuiFingerprint.h` are byte-exact copies of the public DearModdingUI client
contract. They are never edited here; changes come from re-vendoring upstream.

| File | SHA-256 |
|---|---|
| `API.h` | `e9457e94fb2134ba547541a007910aa898f81d22fe6a23f354e6116d10dd7af7` |
| `ImGuiFingerprint.h` | `0376a5a03cd97ff4fe3ff9096b167b4db8c40f7010834bac36c0b7fe0f19105f` |

Vendored from [Addictol](https://github.com/Dear-Modding-FO4/Addictol) by Dear-Modding-FO4, branch
`feat/evil-addictol`, commit `593336cfdd004f3b29ac0fb49eb2122280876cdd`. The API version is
`DMUI_API_VERSION_1_0`.

## What this is not

Fallout4Utils does not depend on, include, or link Addictol. These headers describe a host-neutral
contract: at `kPostPostLoad` the plugin looks for a `DMUI_GetHostAPI` export in any loaded module,
and any module implementing this ABI can host its pages.

Copying rather than submoduling is deliberate. Depending on the host's repository would reintroduce
exactly the coupling the C ABI exists to remove, and would pull an entire tree to obtain two
headers.

## Why vendored drift is safe

The ABI grows by appending to `DMUI_HostAPI` behind size guards such as
`DMUI_HOST_API_REGISTER_ACTION_SIZE`. A stale client never reads past the `structSize` it knows, so
it interoperates correctly with a newer host — it simply does not see the new entry point. Check
both the size and the pointer before calling any appended function.

The drift that *would* be fatal is a moved Dear ImGui pin, and that fails loudly: the fingerprint
assertions in `src/Host/Fingerprint.h` are compile-time, so a mismatch breaks the build rather than
a runtime registration.

## Re-vendoring

Copy both upstream headers without modification, update the commit and SHA-256 values above, then
rebuild. Verify with:

```powershell
Get-FileHash include\DearModdingUI\*.h -Algorithm SHA256
```
