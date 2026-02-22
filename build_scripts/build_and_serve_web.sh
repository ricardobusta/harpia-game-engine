#!/bin/bash
#
# Build Harpia for WebAssembly then immediately serve it locally.
# Usage: ./build_and_serve_web.sh [Release|Debug] [port]
#

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_TYPE="${1:-Debug}"
PORT="${2:-8080}"

echo "== Build & Serve Web"
echo ""

"$SCRIPT_DIR/build_web.sh" "$BUILD_TYPE"

echo ""
"$SCRIPT_DIR/serve_web.sh" "$PORT"