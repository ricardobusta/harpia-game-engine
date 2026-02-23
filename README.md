# Harpia Game Engine

[![Build](https://github.com/ricardobusta/harpia-game-engine/actions/workflows/build.yml/badge.svg)](https://github.com/ricardobusta/harpia-game-engine/actions/workflows/build.yml)

### 28/05/2022
Game Engine made with learning purposes. My idea is to train my knowledge with C++ language and different aspects of engine/ development.

The original engine was started around 2008, with the name of `RGine`, being uploaded to Google Code in 2011 and migrated to Github in 2015. In 2022 I decided to give it another try and see how far I can get.

-- Ricardo Bustamante (aka Busta)

### 22/02/2026

I'm back and I have resurrected my game engine. Now it's improved and have support for other build platforms (Web/ItchIo)

-- Busta
# Building

## Requirements

**All platforms:** CMake 3.22+, Git, a C++17 compiler.

**macOS:** Xcode Command Line Tools (`xcode-select --install`).

**Windows:** MinGW-w64 (GCC) or Visual Studio 2022 (MSVC). PowerShell required for scripts.

**Web:** Python 3 (used by emsdk). The Emscripten SDK is bundled as a submodule.

## Checking out

```bash
git clone --recurse-submodules https://github.com/ricardobusta/harpia-game-engine.git
```

If you already cloned without submodules:

```bash
git submodule update --init --recursive
```

---

## Desktop Build — macOS

**1. Set up asset symlinks** (run once after cloning):

```bash
./build_scripts/create_symlinks.sh
```

**2. Build:**

```bash
mkdir cmake-build-release && cd cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```

Output: `cmake-build-release/bin/`

---

## Desktop Build — Windows

**1. Set up asset symlinks** — open PowerShell **as Administrator**:

```powershell
.\build_scripts\create_symlinks.ps1
```

**2a. Build with MinGW:**

```bash
mkdir cmake-build-release && cd cmake-build-release
cmake .. -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles"
cmake --build . --parallel
```

**2b. Build with Visual Studio 2022:**

```bash
mkdir cmake-build-release && cd cmake-build-release
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

Output: `cmake-build-release/bin/` (DLLs are copied automatically on Windows).

---

## Web Build — macOS / Linux (Emscripten → itch.io)

**1. Install emsdk** (one-time):

```bash
./build_scripts/install_emsdk.sh
```

> **macOS SSL note:** If you see a `CERTIFICATE_VERIFY_FAILED` error, the script handles it automatically via `PYTHONHTTPSVERIFY=0` and the system cert bundle.

**2. Build:**

```bash
./build_scripts/build_web.sh
```

Output in `cmake-build-web/bin/`:

| File | Description |
|------|-------------|
| `Harpia.SampleGame.html` | Open this in a browser to run the game |
| `Harpia.SampleGame.js` | Emscripten JavaScript glue |
| `Harpia.SampleGame.wasm` | WebAssembly binary |
| `Harpia.SampleGame.data` | Preloaded assets |

**3. Test locally** (browsers block WebAssembly over `file://`):

```bash
./build_scripts/serve_web.sh
# Open http://localhost:8080/Harpia.SampleGame.html
```

**4. Package for itch.io:**

```bash
./build_scripts/package_web.sh
```

This creates `itch_upload.zip` in the project root. Upload it to itch.io and set the game kind to **HTML**. If the game doesn't load, enable **SharedArrayBuffer** in the itch.io embed options.

---

## Web Build — Windows (Emscripten)

**1. Install emsdk:**

```powershell
.\build_scripts\install_emsdk.ps1
```

**2. Build** (run from the project root in a shell where emsdk is active):

```powershell
cd harpia\third_party\emsdk
.\emsdk_env.bat
cd ..\..\..
mkdir cmake-build-web
cd cmake-build-web
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel
```

**3. Test locally:**

```powershell
cd cmake-build-web\bin
python -m http.server 8080
# Open http://localhost:8080/Harpia.SampleGame.html
```

---

## Project Structure

```
harpia-game-engine/
├── harpia/                  # Engine library
│   ├── engine/
│   │   ├── audio/           # SDL3_mixer audio system
│   │   ├── core/            # Application loop, input, time
│   │   ├── game/            # Scene and object management
│   │   ├── rendering/       # OpenGL / WebGL rendering
│   │   └── structures/      # Public math types, string utils
│   └── third_party/         # Vendored dependencies
├── sample_game/             # Example game
│   └── assets/              # Shaders, textures, audio, models
└── build_scripts/
    ├── create_symlinks.sh   # macOS asset symlink setup
    ├── create_symlinks.ps1  # Windows asset symlink setup
    ├── install_emsdk.sh     # macOS/Linux emsdk install
    ├── install_emsdk.ps1    # Windows emsdk install
    ├── build_web.sh         # macOS/Linux web build
    └── package_web.sh       # macOS/Linux itch.io packaging
```

## Dependencies (vendored as submodules)

| Library | Purpose |
|---------|---------|
| SDL3 | Windowing, input, audio backend |
| SDL3_mixer | Audio playback |
| SDL3_image | Texture loading |
| SDL3_ttf | Font rendering |
| GLM | Math (internal only) |
| GL3W | Desktop OpenGL loader (not used in web builds) |
| OpenFBX | FBX model loading |
| emsdk | Emscripten SDK for WebAssembly |

---

# Useful Links

## Google Test
- https://google.github.io/googletest/primer.html

## EMScripten
- https://emscripten.org/docs/introducing_emscripten/about_emscripten.html
- https://stackoverflow.com/questions/51868832/integrate-emscripten-in-clion/72578219#72578219
- https://gist.github.com/WesThorburn/00c47b267a0e8c8431e06b14997778e4

## Lazy Foo'
Good old SDL tutorials — https://lazyfoo.net/tutorials/SDL/index.php

## Math libs
- https://github.com/sgorsten/linalg/blob/main/linalg.h
- https://github.com/g-truc/glm
