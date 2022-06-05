//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//
#include "Debug.h"

#ifdef HARPIA_DEBUG

#include <SDL_log.h>

namespace Harpia {
    void Debug::Log(const char *tag, const char *message) {
        std::cout << "INFO: [" << tag << "] " << message << std::endl;
        //SDL_Log("[%s] %s", tag, message);
    }

    void Debug::LogWarning(const char *tag, const char *message) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }

    void Debug::LogError(const char *tag, const char *message) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }
}

#endif