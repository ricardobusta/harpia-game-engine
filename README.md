# Harpia Game Engine

[![tests](https://github.com/ricardobusta/harpia-game-engine/actions/workflows/tests.yml/badge.svg)](https://github.com/ricardobusta/harpia-game-engine/actions/workflows/tests.yml)

Game Engine made with learning purposes. My idea is to train my knowledge with C++ language and different aspects of engine/ development.

The original engine was started around 2008, with the name of `RGine`, being uploaded to Google Code in 2011 and migrated to Github in 2015. In 2022 I decided to give it another try and see how far I can get.

-- Ricardo Bustamante (aka Busta)

# Configuration

## Checking out

Important to run:
```
git submodule update --init --recursive
```
to make sure all SDL submodules were checked out.

## EMScripten Setup

```
# Download and install the latest SDK tools.
.\emsdk.bat install latest
# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
.\emsdk.bat activate latest
# Activate PATH and other environment variables in the current terminal
./emsdk_env.bat
```

# Useful Links

## Google Test
- https://google.github.io/googletest/primer.html
- 

## EMScripten
For compiling the project into a web application
https://emscripten.org/docs/introducing_emscripten/about_emscripten.html
https://tech-de.netlify.app/articles/de522284/index.html
https://stackoverflow.com/questions/51868832/integrate-emscripten-in-clion
https://stackoverflow.com/questions/51868832/integrate-emscripten-in-clion/72578219#72578219
https://gist.github.com/WesThorburn/00c47b267a0e8c8431e06b14997778e4

## Lazy Foo'
Good old SDL tutorials
https://lazyfoo.net/tutorials/SDL/index.php

## Math libs
- https://github.com/sgorsten/linalg/blob/main/linalg.h
- https://github.com/g-truc/glm
