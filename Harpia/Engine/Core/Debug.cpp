//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Debug.h"

#include <SDL_log.h>

namespace Harpia {
    void Debug::Print(const char *tag, const char *message) {
        SDL_Log("[%s] %s", tag, message);
    }

    void Debug::PrintWarning(const char *tag, const char *message) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }

    void Debug::PrintError(const char *tag, const char *message) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }
}