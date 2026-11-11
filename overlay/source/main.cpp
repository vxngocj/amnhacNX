#include <switch.h>
#include <cstdio>
#include <dirent.h>
#include <string>
#include <vector>

#include "settings.hpp"

namespace amnhacNX {

static void printHeader(const Settings& settings) {
    std::printf("===================================\n");
    std::printf("amnhacNX overlay stub\n");
    std::printf("Language: %s\n", settings.language == Language::Vietnamese ? "Tiếng Việt" : "English");
    std::printf("Music volume: %.2f\n", settings.musicVolume);
    std::printf("Game volume: %.2f\n", settings.gameVolume);
    std::printf("===================================\n\n");
}

static std::vector<Track> scanMusic(const std::string& directory) {
    return listMusicTracks(directory);
}

int main() {
    consoleInit(nullptr);

    Settings settings;
    std::string settingsPath = "/switch/amnhacNX/settings.ini";
    std::string musicDirectory = "/switch/amnhacNX/music/";

    loadSettings(settingsPath, settings);
    std::vector<Track> tracks = scanMusic(musicDirectory);

    printHeader(settings);
    std::printf("Found tracks: %zu\n", tracks.size());
    for (std::size_t i = 0; i < tracks.size() && i < 10; ++i) {
        std::printf("[%zu] %s\n", i + 1, tracks[i].title.c_str());
    }

    std::printf("\nControls:\n");
    std::printf("A = Play/Pause\n");
    std::printf("DPad Up/Down = Change selection\n");
    std::printf("X = Toggle language\n");
    std::printf("Plus = Exit\n");

    std::size_t selectedIndex = 0;
    bool playing = false;

    while (appletMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_UP) {
            if (selectedIndex > 0) {
                --selectedIndex;
            }
        }

        if (kDown & KEY_DOWN) {
            if (selectedIndex + 1 < tracks.size()) {
                ++selectedIndex;
            }
        }

        if (kDown & KEY_A) {
            playing = !playing;
        }

        if (kDown & KEY_X) {
            settings.language = (settings.language == Language::English) ? Language::Vietnamese : Language::English;
            saveSettings(settingsPath, settings);
        }

        if (kDown & KEY_PLUS) {
            break;
        }

        consoleClear();
        printHeader(settings);
        std::printf("Now playing: %s\n", tracks.empty() ? "(none)" : tracks[selectedIndex].title.c_str());
        std::printf("Status: %s\n", playing ? "Playing" : "Paused");
        std::printf("Selection: %zu/%zu\n", selectedIndex + 1, tracks.size());
        std::printf("\nControls:\n");
        std::printf("A = Play/Pause\n");
        std::printf("DPad Up/Down = Change selection\n");
        std::printf("X = Toggle language\n");
        std::printf("Plus = Exit\n");

        consoleUpdate(nullptr);
    }

    consoleExit(nullptr);
    return 0;
}

} // namespace amnhacNX
