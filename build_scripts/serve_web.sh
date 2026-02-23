#!/bin/bash
#
# Serve the web build locally for testing
# Usage: ./serve_web.sh [port] [build_dir]
#

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/.."
PORT="${1:-8080}"
BUILD_DIR="${2:-$PROJECT_DIR/build/web/bin}"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Error: Build output not found at $BUILD_DIR"
    echo "Run build_web.sh first."
    exit 1
fi

echo "== Serving web build at http://localhost:$PORT"
echo "   Open: http://localhost:$PORT/Harpia.SampleGame.html"
echo "   Press Ctrl+C to stop."
echo ""

cd "$BUILD_DIR"
python3 -m http.server "$PORT"
