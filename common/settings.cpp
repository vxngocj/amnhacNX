#include "settings.hpp"

namespace amnhacNX {

const char* Translation::appTitle(Language lang) {
    return lang == Language::Vietnamese ? "amnhacNX" : "amnhacNX";
}

const char* Translation::settings(Language lang) {
    return lang == Language::Vietnamese ? "Cài đặt" : "Settings";
}

const char* Translation::language(Language lang) {
    return lang == Language::Vietnamese ? "Ngôn ngữ" : "Language";
}

const char* Translation::musicVolume(Language lang) {
    return lang == Language::Vietnamese ? "Âm lượng nhạc" : "Music volume";
}

const char* Translation::gameVolume(Language lang) {
    return lang == Language::Vietnamese ? "Âm lượng game" : "Game volume";
}

const char* Translation::play(Language lang) {
    return lang == Language::Vietnamese ? "Phát" : "Play";
}

const char* Translation::pause(Language lang) {
    return lang == Language::Vietnamese ? "Tạm dừng" : "Pause";
}

} // namespace amnhacNX
