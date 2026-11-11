#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BIN="${TMPDIR:-/tmp}/amnhacnx-settings-test"

c++ -std=c++17 -Wall -Wextra -I"${ROOT}/common" \
    "${ROOT}/tests/settings_test.cpp" "${ROOT}/common/settings.cpp" -o "${BIN}"
"${BIN}"
rm -f "${BIN}"

echo "Host settings tests passed."
