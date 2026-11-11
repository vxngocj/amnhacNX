#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 1 ]]; then
    echo "Usage: $0 /path/to/mounted/sd" >&2
    exit 2
fi

SD_ROOT="$(cd "$1" && pwd)"
mkdir -p "${SD_ROOT}/switch/amnhacNX/music"
cat > "${SD_ROOT}/switch/amnhacNX/settings.ini" <<'EOF'
language = en
music_volume = 0.80
game_volume = 0.60
auto_play = true
loop_track = true
overlay_enabled = true
EOF

echo "Prepared ${SD_ROOT}/switch/amnhacNX/music"
