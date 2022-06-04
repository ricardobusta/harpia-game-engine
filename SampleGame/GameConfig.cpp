//
// Created by ricar on 01/06/2022.
//

#include "GameConfig.h"

#include <SDL.h>

void GameConfig::Configure(Harpia::Configuration &configuration) {
    configuration.game.gameTitle = "Harpia Sample";
    configuration.game.clearColor = Harpia::Color(0.5f, 0.f, 0.f);

    configuration.window.windowSize = Harpia::Vector2Int(640, 480);

    configuration.input.mappedKeys.push_back(SDLK_UP);
    configuration.input.mappedKeys.push_back(SDLK_DOWN);
    configuration.input.mappedKeys.push_back(SDLK_LEFT);
    configuration.input.mappedKeys.push_back(SDLK_RIGHT);
}
