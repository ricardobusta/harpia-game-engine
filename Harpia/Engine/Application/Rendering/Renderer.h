//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERER_H
#define HARPIAGAMEENGINE_RENDERER_H

class SDL_Window;

class SDL_Surface;

namespace Harpia {
    class GameConfiguration;
    class Color;

    class Renderer {
    public:
        virtual int GetWindowFlags();

        int Initialize(GameConfiguration &configuration, SDL_Window *window);

        virtual void UpdateFrame();

        virtual void Destroy();
    private:
        virtual int RenderingInitialize();

    protected:
        Color *_clearColor;
        SDL_Window *_window = nullptr;
    private:
        SDL_Surface *_surface = nullptr;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_RENDERER_H
