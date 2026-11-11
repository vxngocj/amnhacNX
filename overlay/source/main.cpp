#define TESLA_INIT_IMPL
#include <tesla.hpp>
#include <switch.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

constexpr const char* kMusicDirectory = "/switch/amnhacNX/music";
constexpr std::size_t kMaxTracks = 512;

FsFileSystem g_sd{};
bool g_sdReady = false;
bool g_vietnamese = false;
std::string g_selectedTrack;
std::vector<std::string> g_tracks;

const char* text(const char* english, const char* vietnamese) {
    return g_vietnamese ? vietnamese : english;
}

bool hasSupportedExtension(const char* filename) {
    const std::string name(filename);
    const std::size_t dot = name.find_last_of('.');
    if (dot == std::string::npos) return false;

    std::string extension = name.substr(dot);
    std::transform(extension.begin(), extension.end(), extension.begin(), [](unsigned char ch) {
        return static_cast<char>(std::tolower(ch));
    });

    return extension == ".mp3" || extension == ".flac" || extension == ".wav" ||
           extension == ".wave" || extension == ".ogg";
}

void scanMusic() {
    g_tracks.clear();
    if (!g_sdReady) return;

    FsDir directory{};
    if (R_FAILED(fsFsOpenDirectory(&g_sd, kMusicDirectory,
                                   FsDirOpenMode_ReadFiles | FsDirOpenMode_NoFileSize,
                                   &directory))) {
        return;
    }

    std::array<FsDirectoryEntry, 32> entries{};
    s64 count = 0;
    while (g_tracks.size() < kMaxTracks &&
           R_SUCCEEDED(fsDirRead(&directory, &count, entries.size(), entries.data())) && count > 0) {
        for (s64 i = 0; i < count && g_tracks.size() < kMaxTracks; ++i) {
            const FsDirectoryEntry& entry = entries[static_cast<std::size_t>(i)];
            if (entry.type == FsDirEntryType_File && hasSupportedExtension(entry.name)) {
                g_tracks.emplace_back(entry.name);
            }
        }
    }
    fsDirClose(&directory);

    std::sort(g_tracks.begin(), g_tracks.end(), [](const std::string& lhs, const std::string& rhs) {
        return strcasecmp(lhs.c_str(), rhs.c_str()) < 0;
    });
}

class MainGui final : public tsl::Gui {
public:
    tsl::elm::Element* createUI() override {
        auto* list = new tsl::elm::List();
        list->addItem(new tsl::elm::CategoryHeader("amnhacNX - Tesla prototype"));
        list->addItem(new tsl::elm::CategoryHeader(text("SD music folder", "Thư mục nhạc trên SD")));
        list->addItem(new tsl::elm::CategoryHeader(kMusicDirectory));

        if (!g_sdReady) {
            list->addItem(new tsl::elm::ListItem(text("Could not open SD card", "Không mở được thẻ SD")));
        } else if (g_tracks.empty()) {
            list->addItem(new tsl::elm::ListItem(text("No supported tracks found", "Không tìm thấy bài nhạc phù hợp")));
        } else {
            list->addItem(new tsl::elm::CategoryHeader(text("Tracks (A: select)", "Danh sách (A: chọn)")));
            for (const std::string& track : g_tracks) {
                auto* item = new tsl::elm::ListItem(track, track == g_selectedTrack ? "Selected" : "");
                item->setClickListener([track](u64 keys) {
                    if (keys & HidNpadButton_A) {
                        g_selectedTrack = track;
                        tsl::changeTo<MainGui>();
                        return true;
                    }
                    return false;
                });
                list->addItem(item);
            }
        }

        auto* refresh = new tsl::elm::ListItem(text("Rescan SD card", "Quét lại thẻ SD"));
        refresh->setClickListener([](u64 keys) {
            if (keys & HidNpadButton_A) {
                scanMusic();
                tsl::changeTo<MainGui>();
                return true;
            }
            return false;
        });
        list->addItem(refresh);

        auto* language = new tsl::elm::ListItem(
            text("Language: English (A to switch)", "Ngôn ngữ: Tiếng Việt (A để đổi)"));
        language->setClickListener([](u64 keys) {
            if (keys & HidNpadButton_A) {
                g_vietnamese = !g_vietnamese;
                tsl::changeTo<MainGui>();
                return true;
            }
            return false;
        });
        list->addItem(language);

        list->addItem(new tsl::elm::CategoryHeader(text("Playback is not in this prototype yet",
                                                         "Bản thử nghiệm này chưa phát nhạc")));
        if (!g_selectedTrack.empty()) {
            list->addItem(new tsl::elm::ListItem(
                text("Selected track", "Bài đã chọn"), g_selectedTrack));
        }
        return list;
    }
};

class AmnhacNxOverlay final : public tsl::Overlay {
public:
    void initServices() override {
        g_sdReady = R_SUCCEEDED(fsOpenSdCardFileSystem(&g_sd));
        scanMusic();
    }

    void exitServices() override {
        if (g_sdReady) {
            fsFsClose(&g_sd);
            g_sdReady = false;
        }
    }

    std::unique_ptr<tsl::Gui> loadInitialGui() override {
        return std::make_unique<MainGui>();
    }
};

} // namespace

int main(int argc, char** argv) {
    return tsl::loop<AmnhacNxOverlay>(argc, argv);
}
