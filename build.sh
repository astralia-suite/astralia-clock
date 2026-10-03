#!/usr/bin/env bash
# Usage: ./build.sh [install]
set -euo pipefail
cd "$(dirname "$0")"

[ -d build ] || meson setup build --prefix=/usr
meson compile -C build
meson test -C build --print-errorlogs

if [ "${1:-}" = install ]; then
    sudo meson install -C build
fi
