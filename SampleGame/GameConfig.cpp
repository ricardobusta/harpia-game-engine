//
// Created by ricar on 01/06/2022.
//

#include "GameConfig.h"

#include <SDL.h>
namespace SampleGame {

    void GameConfig::Configure(Harpia::Configuration &configuration) {
        configuration.game.title = "Harpia Sample";
        configuration.game.clearColor = Harpia::Color(0.5f, 0.f, 0.f);

        configuration.window.size = Harpia::Vector2Int(640, 480);

        configuration.input.mappedKeys.insert(configuration.input.mappedKeys.end(), {
                SDLK_UP,
                SDLK_DOWN,
                SDLK_LEFT,
                SDLK_RIGHT
        });

        configuration.game.scenes.insert(configuration.game.scenes.end(), {

        });
    }
}