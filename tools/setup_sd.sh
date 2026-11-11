#!/usr/bin/env bash
set -e

# Minimal helper script used during development.
# It creates the expected SD folder layout for amnhacNX.

mkdir -p /switch/amnhacNX/music
mkdir -p /switch/amnhacNX/config

cat > /switch/amnhacNX/config/settings.ini <<'EOF'
[general]
language = en
music_volume = 0.80
game_volume = 0.60
auto_play = true
loop_track = true
overlay_enabled = true
EOF

echo "amnhacNX SD folders prepared."
