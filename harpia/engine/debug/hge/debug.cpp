//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//
#include "debug.h"

#ifdef HARPIA_DEBUG

#include <SDL_log.h>

namespace Harpia {
    void Debug::Log(const char *tag, const char *message) {
        SDL_Log("[%s] %s", tag, message);
    }

    void Debug::LogWarning(const char *tag, const char *message) {
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }

    void Debug::LogError(const char *tag, const char *file, int line, const char *message) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s at %s:%d", tag, message, file, line);
    }

    std::basic_string_view<char> Debug::CallerName(const std::string_view &s) {
        size_t end = s.find('(');
        size_t begin = s.substr(0, end).rfind(' ') + 1;
        size_t size = end - begin;
        return s.substr(begin, size);
    }
}// namespace Harpia

#endif