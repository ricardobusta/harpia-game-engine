#!/bin/bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"

ln -sf "$PROJECT_DIR/sample_game/assets" "$PROJECT_DIR/cmake-build-debug/bin/assets"
