#pragma once

#include <stdint.h>

/*
 * amnhacNX v1 overlay <-> background-player IPC contract.
 *
 * This header deliberately contains only fixed-width POD types so it can be
 * included by both the Tesla overlay and the background service. It defines
 * the wire contract only; it is not an implemented audio backend yet.
 */
#define AMNHACNX_IPC_SERVICE_NAME "amnhac"
#define AMNHACNX_IPC_API_VERSION 1
#define AMNHACNX_IPC_MAX_PATH 512

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AmnhacNxCommand {
    AmnhacNxCommand_GetStatus = 0,
    AmnhacNxCommand_PlayPath = 1,
    AmnhacNxCommand_TogglePause = 2,
    AmnhacNxCommand_Next = 3,
    AmnhacNxCommand_Previous = 4,
    AmnhacNxCommand_Stop = 5,
    AmnhacNxCommand_SetMusicVolume = 6,
    AmnhacNxCommand_GetApiVersion = 7
} AmnhacNxCommand;

typedef enum AmnhacNxPlaybackState {
    AmnhacNxPlaybackState_Stopped = 0,
    AmnhacNxPlaybackState_Playing = 1,
    AmnhacNxPlaybackState_Paused = 2,
    AmnhacNxPlaybackState_Error = 3
} AmnhacNxPlaybackState;

typedef struct AmnhacNxPlaybackInfo {
    uint32_t api_version;
    uint32_t state;
    uint32_t music_volume_percent;
    char current_path[AMNHACNX_IPC_MAX_PATH];
} AmnhacNxPlaybackInfo;

#ifdef __cplusplus
}
#endif
