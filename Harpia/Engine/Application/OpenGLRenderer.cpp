//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/05/2022.
//

#include "OpenGLRenderer.h"

//#include <SDL.h>
//#include <GL/glew.h>
//#include <SDL_opengl.h>

#include "Debug.h"

namespace Harpia::Engine {
//    bool OpenGLRenderer::Start(SDL_Window *window) {
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//        _context = SDL_GL_CreateContext(window);
//        if (_context == nullptr) {
//            printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
//            return false;
//        } else {
//            glewExperimental = GL_TRUE;
//            GLenum glewError = glewInit();
//            if (glewError != GLEW_OK) {
//                printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
//            }
//
//            //Use Vsync
//            if (SDL_GL_SetSwapInterval(1) < 0) {
//                printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
//            }
//
//            //Initialize OpenGL
//            if (!InitGL()) {
//                printf("Unable to initialize OpenGL!\n");
//                return false;
//            }
//        }
//
//        return true;
//    }
//
//    bool OpenGLRenderer::InitGL() {
//
//    }
}