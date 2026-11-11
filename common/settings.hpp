#pragma once

#include <string>

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
    bool overlayEnabled = true;
};

struct Translation {
    static const char* appTitle(Language lang);
    static const char* settings(Language lang);
    static const char* language(Language lang);
    static const char* musicVolume(Language lang);
    static const char* gameVolume(Language lang);
    static const char* play(Language lang);
    static const char* pause(Language lang);
};

} // namespace amnhacNX
