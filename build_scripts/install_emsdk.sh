#!/bin/bash
#
# Install and activate the Emscripten SDK
# Usage: ./install_emsdk.sh
#

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
EMSDK_DIR="$SCRIPT_DIR/../harpia/third_party/emsdk"

if [ ! -d "$EMSDK_DIR" ]; then
    echo "Error: emsdk directory not found at $EMSDK_DIR"
    echo "Make sure the emsdk submodule is initialized:"
    echo "  git submodule update --init --recursive"
    exit 1
fi

cd "$EMSDK_DIR"

# Suppress Python SSL verification (needed on macOS when root certs aren't installed).
# Also point to the macOS system cert bundle as a fallback.
export PYTHONHTTPSVERIFY=0
export SSL_CERT_FILE=/etc/ssl/cert.pem

echo "== Installing latest emsdk..."
./emsdk install latest

echo "== Activating latest emsdk..."
./emsdk activate latest

echo ""
echo "== emsdk installed and activated!"
echo "   To use in your current shell, run:"
echo "     source $EMSDK_DIR/emsdk_env.sh"
