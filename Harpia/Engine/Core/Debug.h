//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_DEBUG_H
#define HARPIAGAMEENGINE_DEBUG_H

#define HARPIA_DEBUG

#include "String.h"

#ifdef HARPIA_DEBUG
#define DebugLog(args...) do {Harpia::Debug::Log(args);} while(0)
#define DebugLogWarning(args...) do {Harpia::Debug::LogWarning(args);} while(0)
#define DebugLogError(args...) do {Harpia::Debug::LogError(args);} while(0)
#else
#define DebugLog(args...)
#define DebugLogWarning(args...)
#define DebugLogError(args...)
#endif

namespace Harpia {
    class Debug {
    public:
        static void Log(const char *message) {
            Print(message);
        }

        static void LogWarning(const char *message) {
            PrintWarning(message);
        }

        static void LogError(const char *message) {
            PrintError(message);
        }

        template<typename... Args>
        static void Log(const char *format, Args ... args) {
            Print(String::Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogWarning(const char *format, Args ... args) {
            PrintWarning(String::Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogError(const char *format, Args ... args) {
            PrintError(String::Format(format, args...).c_str());
        }

    public:
        static void Print(const char *message);

        static void PrintWarning(const char *message);

        static void PrintError(const char *message);
    };
}

#endif //HARPIAGAMEENGINE_DEBUG_H
