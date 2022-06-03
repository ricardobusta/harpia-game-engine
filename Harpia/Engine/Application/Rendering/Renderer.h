//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_H
#define HARPIAGAMEENGINE_RENDERER_H

class SDL_Window;

class SDL_Surface;

namespace Harpia {
    class Configuration;

    class Renderer {
    public:
        virtual int GetWindowFlags();

        virtual int Initialize(Configuration *configuration, SDL_Window *window);

        virtual void UpdateFrame();

        virtual void Destroy();
    private:
        Configuration *_configuration = nullptr;
        SDL_Surface *_surface = nullptr;
        SDL_Window *_window = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERER_H
