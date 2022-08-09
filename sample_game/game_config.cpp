//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 01/06/2022.
//

#include "game_config.h"
#include "all_the_things_scene.h"
#include "main_scene.h"
#include "spaceship_scene.h"

#include <SDL.h>

namespace SampleGame {
    void GameConfig::Configure(Harpia::Configuration &configuration) {
        configuration.game.title = "Harpia Sample";

        configuration.window.size = Harpia::Vector2Int(800, 600);
        configuration.window.resizeable = true;

        configuration.input.mappedKeys.insert(configuration.input.mappedKeys.end(), {
                                                                                            SDLK_1,
                                                                                            SDLK_2,
                                                                                    });

        configuration.game.scenes.insert(configuration.game.scenes.end(), {new MainScene(),
                                                                           new AllTheThingsScene(),
                                                                           new SpaceshipScene()});
    }
}// namespace SampleGame