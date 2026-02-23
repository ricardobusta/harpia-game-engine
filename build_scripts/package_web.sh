#!/bin/bash
#
# Package Emscripten build for itch.io upload
# Usage: ./package_web.sh [build_dir] [output_dir]
#
# Produces a zip file ready to upload to itch.io as an HTML5 game.
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/.."
BUILD_DIR="${1:-$PROJECT_DIR/build/web/bin}"
OUTPUT_DIR="${2:-$PROJECT_DIR/build/itch_upload}"
GAME_NAME="Harpia.SampleGame"

if [ ! -f "$BUILD_DIR/$GAME_NAME.js" ]; then
    echo "Error: Build output not found at $BUILD_DIR/$GAME_NAME.js"
    echo "Run build_web.sh first."
    exit 1
fi

echo "== Packaging web build for itch.io..."
rm -rf "$OUTPUT_DIR"
mkdir -p "$OUTPUT_DIR"

# Copy build artifacts
cp "$BUILD_DIR/$GAME_NAME.html" "$OUTPUT_DIR/index.html"
cp "$BUILD_DIR/$GAME_NAME.js" "$OUTPUT_DIR/"
cp "$BUILD_DIR/$GAME_NAME.wasm" "$OUTPUT_DIR/"

# Copy preloaded data if it exists
if [ -f "$BUILD_DIR/$GAME_NAME.data" ]; then
    cp "$BUILD_DIR/$GAME_NAME.data" "$OUTPUT_DIR/"
fi

# Create zip for itch.io
cd "$OUTPUT_DIR"
zip -r "$PROJECT_DIR/build/itch_upload.zip" .

echo ""
echo "== Package complete!"
echo "   Folder: $OUTPUT_DIR/"
echo "   Zip:    $PROJECT_DIR/build/itch_upload.zip"
echo ""
echo "   Upload build/itch_upload.zip to itch.io as an HTML5 game."
echo "   Set 'SharedArrayBuffer' if needed in itch.io embed settings."
