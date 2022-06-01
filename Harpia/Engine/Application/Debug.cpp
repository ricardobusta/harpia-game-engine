//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Debug.h"
#include "SDL_log.h"

namespace Harpia {
    void Debug::Print(const char *message) {
        SDL_Log("%s", message);
    }

    void Debug::PrintWarning(const char *message) {
        SDL_LogWarn(SDL_LOG_CATEGORY_ERROR, "%s", message);
    }

    void Debug::PrintError(const char *message) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", message);
    }
}