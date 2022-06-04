//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include "Configuration.h"

class SDL_Window;

namespace Harpia {
    class CoreSystem;
    class RenderingSystem;

    class InputSystem;

    class AudioSystem;

    class Application {
    public:
        Configuration configuration;
    private:
        bool _createdWithSuccess = false;
        int _result = -1;

        SDL_Window *_window = nullptr;
        RenderingSystem *_renderSystem = nullptr;
        InputSystem *_inputSystem = nullptr;
        AudioSystem *_audioSystem = nullptr;
    public:
        explicit Application(void(*configure)(Configuration &config));

        ~Application();

        int Execute();

    private:
        int Initialize();

        void Quit();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
