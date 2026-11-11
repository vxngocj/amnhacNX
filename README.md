# amnhacNX

amnhacNX is a Nintendo Switch homebrew project designed to play local music files from the SD card while you are in games or in the system UI. The project follows the same general direction as sys-tune:

- background playback support
- Tesla-style overlay UI
- SD card music scanning
- configurable playback and settings
- English and Vietnamese language options

This repo is the initial scaffolding for the application. It is meant to be built with devkitPro/libnx and Atmosphère-based tooling.

## Features planned

- Music scan from /switch/amnhacNX/
- Playback while in-game
- Overlay controls (play, pause, next, prev, volume)
- Settings screen for language and behavior
- English / Tiếng Việt translations
- Music and game volume controls

## Folder structure

- `overlay/` - Tesla overlay UI
- `sysmodule/` - background audio service / system module skeleton
- `common/` - shared settings, language data, and utilities
- `tools/` - helper scripts

## Building

1. Install devkitPro and libnx.
2. Set `DEVKITPRO` in your environment.
3. Run:

```bash
make
```

4. Package output can be copied into the SD card structure for Atmosphère or overlay loading.

## SD layout

```text
/switch/amnhacNX/
  settings.ini
  music/
    song1.mp3
    song2.flac
    song3.wav
```

## Notes

- This is the foundational skeleton for the project.
- The actual audio engine and full Tesla UI are intended to be expanded in subsequent commits.
- Audio behavior while in games depends on the Switch environment and the target Atmosphère version.
