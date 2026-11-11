# amnhacNX

A Nintendo Switch homebrew music-player project for Atmosphère, inspired by the separation used by projects such as sys-tune: a Tesla overlay for controls and a background audio service for playback.

## Current status: Tesla overlay prototype

The current build is an **overlay prototype**, not a completed music player. It can open the SD card, scan `/switch/amnhacNX/music` for MP3, FLAC, WAV/WAVE and OGG filenames, show the list in Tesla, and switch the UI language between English and Vietnamese. Selecting a file only marks it in the UI; **audio playback, persistent overlay settings, and the background sysmodule are not implemented yet**. This prototype does not change game volume.

This distinction is intentional: a Tesla overlay alone cannot keep audio playing after it closes. Background playback needs a real sysmodule/audio backend and IPC, which is a separate implementation step.

## Requirements

- Nintendo Switch homebrew development environment: devkitPro, libnx, and `switch-dev`.
- Tesla overlay headers from [libtesla](https://github.com/WerWolv/libtesla).
- Atmosphère and Tesla/nx-ovlloader on the device to load an `.ovl` file.

Set `DEVKITPRO` and `DEVKITARM`. Fetch the Tesla headers once:

```sh
./tools/setup_deps.sh
```

Build the overlay:

```sh
make
```

The output is `overlay/amnhacNX-overlay.ovl`. Building on hardware has not been verified by this repository's CI; see `tools/test.sh` for host-side settings tests.

## SD card

Create this folder and place your own supported audio files there:

```text
/switch/amnhacNX/music/
```

The setup helper can prepare it on a mounted SD card, for example:

```sh
./tools/setup_sd.sh /path/to/mounted/sd
```

## Controls in this prototype

- Use D-pad to move through the Tesla list.
- A selects a listed track or switches the UI language.
- The selected filename is displayed in the overlay.
- The playback entry is explicitly marked unavailable until the background audio service is implemented.

## Planned work

1. Implement a background audio service, audio decoding/output, and a versioned IPC interface.
2. Connect Tesla overlay controls to that service (play/pause, next/previous, music volume).
3. Persist English/Vietnamese settings and provide localized settings screens.
4. Investigate whether separate per-title game-volume control is supported; it is not promised by this prototype.
5. Package and test on a Switch with a documented Atmosphère/Tesla setup.

Only use audio files you own or are authorized to use.
