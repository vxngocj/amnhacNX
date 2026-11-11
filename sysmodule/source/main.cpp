#include <switch.h>
#include <cstdio>
#include <string>
#include <vector>

namespace amnhacNX {

enum class AudioDriverState {
    Idle,
    Playing,
    Paused,
    Error
};

struct Track {
    std::string path;
    std::string title;
};

struct SystemConfig {
    std::string musicDirectory = "/switch/amnhacNX/music/";
    std::string settingsFile = "/switch/amnhacNX/settings.ini";
    float musicVolume = 0.80f;
    float gameVolume = 0.60f;
    bool loop = true;
    bool autoPlay = true;
    bool overlayEnabled = true;
};

static void printSystemInfo(const SystemConfig& cfg) {
    std::printf("amnhacNX sysmodule skeleton\n");
    std::printf("musicDir: %s\n", cfg.musicDirectory.c_str());
    std::printf("settingsFile: %s\n", cfg.settingsFile.c_str());
    std::printf("musicVolume: %.2f\n", cfg.musicVolume);
    std::printf("gameVolume: %.2f\n", cfg.gameVolume);
}

} // namespace amnhacNX

int main() {
    consoleInit(nullptr);

    amnhacNX::SystemConfig cfg;
    amnhacNX::printSystemInfo(cfg);

    std::printf("Background audio service initialized.\n");
    std::printf("Overlay: enabled\n");

    while (appletMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
            break;
        }

        consoleUpdate(nullptr);
    }

    consoleExit(nullptr);
    return 0;
}
