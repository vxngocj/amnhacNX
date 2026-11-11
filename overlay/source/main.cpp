#include <switch.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace amnhacNX {

enum class Language {
    English,
    Vietnamese
};

struct Settings {
    Language language = Language::English;
    float musicVolume = 0.80f;
    float gameVolume = 0.60f;
    bool autoPlay = true;
    bool loopTrack = true;
    bool showOverlay = true;
};

static const char* langueName(Language lang) {
    switch (lang) {
        case Language::English: return "English";
        case Language::Vietnamese: return "Tiếng Việt";
        default: return "English";
    }
}

static const char* getText(const char* key, Language lang) {
    // Minimal translation table for the initial skeleton.
    if (lang == Language::Vietnamese) {
        if (std::strcmp(key, "title") == 0) return "amnhacNX";
        if (std::strcmp(key, "settings") == 0) return "Cài đặt";
        if (std::strcmp(key, "music_volume") == 0) return "Âm lượng nhạc";
        if (std::strcmp(key, "game_volume") == 0) return "Âm lượng game";
        if (std::strcmp(key, "play") == 0) return "Phát";
        if (std::strcmp(key, "pause") == 0) return "Tạm dừng";
        if (std::strcmp(key, "language") == 0) return "Ngôn ngữ";
        return "";
    }

    if (std::strcmp(key, "title") == 0) return "amnhacNX";
    if (std::strcmp(key, "settings") == 0) return "Settings";
    if (std::strcmp(key, "music_volume") == 0) return "Music volume";
    if (std::strcmp(key, "game_volume") == 0) return "Game volume";
    if (std::strcmp(key, "play") == 0) return "Play";
    if (std::strcmp(key, "pause") == 0) return "Pause";
    if (std::strcmp(key, "language") == 0) return "Language";
    return "";
}

} // namespace amnhacNX

int main() {
    consoleInit(nullptr);

    amnhacNX::Settings settings;
    amnhacNX::Language currentLanguage = settings.language;

    std::printf("%s\n", amnhacNX::getText("title", currentLanguage));
    std::printf("%s: %s\n", amnhacNX::getText("language", currentLanguage), amnhacNX::langueName(currentLanguage));
    std::printf("%s: %.2f\n", amnhacNX::getText("music_volume", currentLanguage), settings.musicVolume);
    std::printf("%s: %.2f\n", amnhacNX::getText("game_volume", currentLanguage), settings.gameVolume);
    std::printf("%s\n", amnhacNX::getText("play", currentLanguage));

    while (appletMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) {
            break;
        }

        // A very simple placeholder overlay interaction.
        if (kDown & KEY_A) {
            std::printf("[A] Toggle playback\n");
        }

        consoleUpdate(nullptr);
    }

    consoleExit(nullptr);
    return 0;
}
