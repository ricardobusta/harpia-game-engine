//
// Created by ricar on 01/06/2022.
//

#include "GameConfig.h"

#include <SDL.h>

void GameConfig::Configure(Harpia::Engine::Configuration *configuration) {
    configuration->gameTitle = "Harpia Sample";
    configuration->clearColor = Harpia::Engine::Color(0.5f, 0.f, 0.f);
    configuration->windowSize = Harpia::Engine::Vector2Int(640, 480);

    configuration->mappedKeys->push_back(SDLK_UP);
    configuration->mappedKeys->push_back(SDLK_DOWN);
    configuration->mappedKeys->push_back(SDLK_LEFT);
    configuration->mappedKeys->push_back(SDLK_RIGHT);
}
