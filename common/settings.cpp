#include "settings.hpp"

#include <algorithm>
#include <cctype>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>

namespace amnhacNX {

static std::string trim(const std::string& value) {
    std::size_t start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        ++start;
    }

    std::size_t end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        --end;
    }

    return value.substr(start, end - start);
}

const char* Translation::appTitle(Language lang) {
    return "amnhacNX";
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

const char* Translation::next(Language lang) {
    return lang == Language::Vietnamese ? "Tiếp theo" : "Next";
}

const char* Translation::previous(Language lang) {
    return lang == Language::Vietnamese ? "Trước đó" : "Previous";
}

const char* Translation::directory(Language lang) {
    return lang == Language::Vietnamese ? "Thư mục" : "Directory";
}

const char* Translation::status(Language lang) {
    return lang == Language::Vietnamese ? "Trạng thái" : "Status";
}

const char* Translation::overlay(Language lang) {
    return lang == Language::Vietnamese ? "Overlay" : "Overlay";
}

std::string languageToString(Language language) {
    return language == Language::Vietnamese ? "vi" : "en";
}

Language parseLanguage(const std::string& value) {
    std::string normalized = trim(value);
    std::transform(normalized.begin(), normalized.end(), normalized.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });

    if (normalized == "vi" || normalized == "vie" || normalized == "vietnamese") {
        return Language::Vietnamese;
    }

    return Language::English;
}

bool loadSettings(const std::string& path, Settings& settings) {
    std::ifstream input(path.c_str());
    if (!input.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(input, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == ';' || trimmed[0] == '#') {
            continue;
        }

        std::size_t pos = trimmed.find('=');
        if (pos == std::string::npos) {
            continue;
        }

        std::string key = trim(trimmed.substr(0, pos));
        std::string value = trim(trimmed.substr(pos + 1));

        if (key == "language") {
            settings.language = parseLanguage(value);
        } else if (key == "music_volume") {
            settings.musicVolume = std::stof(value);
        } else if (key == "game_volume") {
            settings.gameVolume = std::stof(value);
        } else if (key == "auto_play") {
            settings.autoPlay = (value == "1" || value == "true" || value == "TRUE");
        } else if (key == "loop_track") {
            settings.loopTrack = (value == "1" || value == "true" || value == "TRUE");
        } else if (key == "overlay_enabled") {
            settings.overlayEnabled = (value == "1" || value == "true" || value == "TRUE");
        }
    }

    return true;
}

bool saveSettings(const std::string& path, const Settings& settings) {
    std::ofstream output(path.c_str(), std::ios::out | std::ios::trunc);
    if (!output.is_open()) {
        return false;
    }

    output << "language = " << languageToString(settings.language) << "\n";
    output << "music_volume = " << settings.musicVolume << "\n";
    output << "game_volume = " << settings.gameVolume << "\n";
    output << "auto_play = " << (settings.autoPlay ? "true" : "false") << "\n";
    output << "loop_track = " << (settings.loopTrack ? "true" : "false") << "\n";
    output << "overlay_enabled = " << (settings.overlayEnabled ? "true" : "false") << "\n";
    return true;
}

std::vector<Track> listMusicTracks(const std::string& directory) {
    std::vector<Track> tracks;
    DIR* dir = opendir(directory.c_str());
    if (!dir) {
        return tracks;
    }

    struct dirent* entry = nullptr;
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        if (name == "." || name == "..") {
            continue;
        }

        std::string lower = name;
        std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });

        bool supported = lower.find(".mp3") != std::string::npos ||
                          lower.find(".flac") != std::string::npos ||
                          lower.find(".wav") != std::string::npos ||
                          lower.find(".ogg") != std::string::npos;

        if (supported) {
            Track track;
            track.path = directory + name;
            track.title = name;
            tracks.push_back(track);
        }
    }

    closedir(dir);
    std::sort(tracks.begin(), tracks.end(), [](const Track& a, const Track& b) {
        return a.title < b.title;
    });
    return tracks;
}

} // namespace amnhacNX
