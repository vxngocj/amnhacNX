#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
DEST="${ROOT}/overlay/lib"

if [[ -f "${DEST}/include/tesla.hpp" ]]; then
    echo "libtesla headers already present: ${DEST}"
    exit 0
fi

if [[ -e "${DEST}" ]]; then
    echo "${DEST} exists but does not contain include/tesla.hpp; refusing to overwrite it." >&2
    exit 1
fi

git clone --depth 1 https://github.com/WerWolv/libtesla.git "${DEST}"
echo "Fetched libtesla headers to ${DEST}"
