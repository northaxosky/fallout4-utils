# Fallout 4 Utils

An F4SE plugin providing in-game tooling for developing and testing Fallout 4 mods.

Early work in progress. The feature set is still being decided.

## Requirements

- [Fallout 4 Script Extender (F4SE)](https://f4se.silverlock.org/)
- [Address Library for F4SE Plugins](https://www.nexusmods.com/fallout4/mods/47327) - required at runtime
- [xmake](https://xmake.io/) 3.0 or newer
- Visual Studio 2022 with the Desktop development with C++ workload

Supported runtimes: 1.10.163, 1.10.984, 1.11.240.

## Building

Clone with `--recurse-submodules`, then:

```
xmake config --mode=release
xmake build
```

The plugin builds to `build/windows/x64/release/Fallout4Utils.dll`. If the repository was cloned
without submodules, run `git submodule update --init --recursive` first.

## Installing

`xmake install` copies the plugin and its symbols into `F4SE/Plugins` under the path given by one
of these environment variables, whichever is set first:

| Variable | Meaning |
| --- | --- |
| `XSE_FO4_MODS_PATH` | A mod manager's mods directory. The plugin installs into its own mod folder. |
| `XSE_FO4_GAME_PATH` | The Fallout 4 install directory. The plugin installs into `Data`. |

## License

GPL-3.0. See [LICENSE](LICENSE).
