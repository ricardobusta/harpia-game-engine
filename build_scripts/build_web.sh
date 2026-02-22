#!/bin/bash
#
# Build Harpia Game Engine for WebAssembly using Emscripten
# Usage: ./build_web.sh [Release|Debug]
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_DIR="$SCRIPT_DIR/.."
EMSDK_DIR="$PROJECT_DIR/harpia/third_party/emsdk"
BUILD_TYPE="${1:-Release}"
BUILD_DIR="$PROJECT_DIR/cmake-build-web"

# Verify emsdk is installed
if [ ! -f "$EMSDK_DIR/emsdk_env.sh" ]; then
    echo "Error: emsdk not found. Run install_emsdk.sh first."
    exit 1
fi

# Activate emsdk
echo "== Activating emsdk..."
source "$EMSDK_DIR/emsdk_env.sh"

# Clean previous build
if [ -d "$BUILD_DIR" ]; then
    echo "== Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

# Configure and build
echo "== Configuring Emscripten build ($BUILD_TYPE)..."
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"
emcmake cmake "$PROJECT_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

echo "== Building..."
cmake --build . --parallel

echo ""
echo "== Build complete!"
echo "   Output: $BUILD_DIR/bin/"
echo ""
echo "   To test locally:"
echo "     cd $BUILD_DIR/bin"
echo "     python3 -m http.server 8080"
echo "     Open http://localhost:8080/Harpia.SampleGame.html"
