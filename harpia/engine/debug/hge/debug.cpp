//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//
#include "debug.h"

#ifdef HARPIA_DEBUG

#include <SDL3/SDL_log.h>
#include <cstdio>
#include <mutex>

namespace Harpia {
    namespace {
        void SDLCALL HarpiaLogOutput(void *userdata, const int category, const SDL_LogPriority priority, const char *message) {
            (void)userdata;
            (void)category;

            const char *prefix = "";
            if (priority == SDL_LOG_PRIORITY_WARN) {
                prefix = "WARNING: ";
            } else if (priority == SDL_LOG_PRIORITY_ERROR || priority == SDL_LOG_PRIORITY_CRITICAL) {
                prefix = "ERROR: ";
            }

            FILE *stream = (priority == SDL_LOG_PRIORITY_ERROR || priority == SDL_LOG_PRIORITY_CRITICAL)
                               ? stderr
                               : stdout;
            std::fprintf(stream, "%s%s\n", prefix, message);
            std::fflush(stream);
        }

        void EnsureLogOutputConfigured() {
            static std::once_flag configureOnce;
            std::call_once(configureOnce, []() {
                SDL_SetLogOutputFunction(HarpiaLogOutput, nullptr);
            });
        }
    }// namespace

    void Debug::Log(const char *tag, const char *message) {
        EnsureLogOutputConfigured();
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }

    void Debug::LogWarning(const char *tag, const char *message) {
        EnsureLogOutputConfigured();
        SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s", tag, message);
    }

    void Debug::LogError(const char *tag, const char *file, const int line, const char *message) {
        EnsureLogOutputConfigured();
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[%s] %s at %s:%d", tag, message, file, line);
    }

    std::basic_string_view<char> Debug::CallerName(const std::string_view &s) {
        const size_t end = s.find('(');
        const size_t begin = s.substr(0, end).rfind(' ') + 1;
        const size_t size = end - begin;
        return s.substr(begin, size);
    }
}// namespace Harpia

#endif
