# amnhacNX implementation plan

## Current state

The Tesla overlay prototype scans and lists supported audio files from the SD card. It does not decode or output audio. The `sysmodule/` target is not a functional system module. Do not install or advertise the current prototype as a background music player.

## v1 architecture

- **Tesla overlay:** UI, bilingual labels, selecting a file and sending playback commands.
- **Background service:** owns audio decoding/output and continues after the overlay closes.
- **IPC:** versioned service interface in `ipc/amnhac_ipc.h`; both sides must reject unsupported API versions and handle service-not-started errors.
- **Settings:** language and music volume persisted on SD. A game-volume setting may only be exposed after a supported, non-invasive API has been verified; do not imply that changing system volume independently controls game audio.

## Implementation milestones

1. Implement and host-test a versioned IPC client/server, status and playback-control commands.
2. Implement a background audio pipeline using a Switch-compatible decoder/output backend; start with one supported format and add formats only after device tests.
3. Connect overlay selection and play/pause/next/previous/music-volume controls to the service.
4. Persist bilingual settings, handle missing SD folders/files, and test service restart and overlay close/reopen behavior.
5. Build with devkitPro and test on a Switch/Atmosphère/Tesla setup before creating a release ZIP.

## Acceptance criteria for a playable alpha

- Selecting an SD-card track starts audible playback while a game is foregrounded.
- Closing and reopening Tesla does not stop or restart playback.
- Overlay commands report errors instead of claiming success when the service is absent.
- English and Vietnamese labels/settings survive restart.
- Tested audio formats and firmware/toolchain versions are listed in the release notes.

A successful host-side compile is not a substitute for testing audio output and service lifecycle on hardware.
