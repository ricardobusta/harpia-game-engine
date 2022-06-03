//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/05/2022.
//

#include "OpenGLApplication.h"

#include <SDL.h>
#include <SDL_opengl.h>

#include "Debug.h"
#include "Configuration.h"

namespace Harpia {
//    int OpenGLApplication::Initialize() {
//        auto result = SDL_Init(SDL_INIT_VIDEO);
//        if (result < 0) {
//            DebugLogError("SDL was not initialized. SDL_Error: %s\n", SDL_GetError());
//            return result;
//        }
//
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
//        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//        _window = SDL_CreateWindow(configuration->gameTitle.c_str(), SDL_WINDOWPOS_UNDEFINED,
//                                   SDL_WINDOWPOS_UNDEFINED, configuration->windowSize.x, configuration->windowSize.y,
//                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
//        if (_window == nullptr) {
//            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
//            return -1;
//        }
//
//        _context = SDL_GL_CreateContext(_window);
//        if (_context == nullptr) {
//            DebugLogError("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
//            return -1;
//        }
//
//        glewExperimental = GL_TRUE;
//        GLenum glewError = glewInit();
//        if (glewError != GLEW_OK) {
//            DebugLogError("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
//        }
//
//        //Use Vsync
//        if (SDL_GL_SetSwapInterval(1) < 0) {
//            DebugLogError("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
//        }
//
//        //Initialize OpenGL
//        if (!InitGL()) {
//            DebugLogError("Unable to initialize OpenGL!\n");
//            return -1;
//        }
//
//        return 0;
//    }

//    void OpenGLApplication::FrameUpdate() {
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(_programID);
//
//        glEnableVertexAttribArray(_vertexPos2DLocation);
//
//        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
//        glVertexAttribPointer(_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
//        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);
//
//        glDisableVertexAttribArray(_vertexPos2DLocation);
//
//        glUseProgram(0);
//
//        SDL_GL_SwapWindow(_window);
//    }
}