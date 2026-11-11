#pragma once

#include <string>
#include <vector>

namespace amnhacNX {

enum class Language {
    English,
    Vietnamese
};

enum class PlaybackMode {
    Single,
    RepeatAll,
    Shuffle
};

struct Settings {
    Language language = Language::English;
    float musicVolume = 0.80f;
    float gameVolume = 0.60f;
    bool autoPlay = true;
    bool loopTrack = true;
    bool overlayEnabled = true;
    PlaybackMode playbackMode = PlaybackMode::RepeatAll;
};

struct Track {
    std::string path;
    std::string title;
};

struct PlaybackState {
    bool isPlaying = false;
    bool isPaused = false;
    std::size_t selectedIndex = 0;
    std::size_t trackCount = 0;
};

struct Translation {
    static const char* appTitle(Language lang);
    static const char* settings(Language lang);
    static const char* language(Language lang);
    static const char* musicVolume(Language lang);
    static const char* gameVolume(Language lang);
    static const char* play(Language lang);
    static const char* pause(Language lang);
    static const char* next(Language lang);
    static const char* previous(Language lang);
    static const char* directory(Language lang);
    static const char* status(Language lang);
    static const char* overlay(Language lang);
};

bool loadSettings(const std::string& path, Settings& settings);
bool saveSettings(const std::string& path, const Settings& settings);
std::string languageToString(Language language);
Language parseLanguage(const std::string& value);
std::vector<Track> listMusicTracks(const std::string& directory);

} // namespace amnhacNX
