#include "settings.hpp"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
    using namespace amnhacNX;

    assert(std::string(Translation::settings(Language::English)) == "Settings");
    assert(std::string(Translation::settings(Language::Vietnamese)) == "Cài đặt");
    assert(parseLanguage("vi") == Language::Vietnamese);
    assert(parseLanguage("en") == Language::English);

    const std::string path = "/tmp/amnhacnx-settings-test.ini";
    Settings saved;
    saved.language = Language::Vietnamese;
    saved.musicVolume = 0.35f;
    saved.gameVolume = 0.70f;
    saved.autoPlay = false;
    assert(saveSettings(path, saved));

    Settings loaded;
    assert(loadSettings(path, loaded));
    assert(loaded.language == Language::Vietnamese);
    assert(loaded.musicVolume > 0.34f && loaded.musicVolume < 0.36f);
    assert(loaded.gameVolume > 0.69f && loaded.gameVolume < 0.71f);
    assert(!loaded.autoPlay);
    std::remove(path.c_str());
    return 0;
}
