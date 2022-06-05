//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_DEBUG_H
#define HARPIAGAMEENGINE_DEBUG_H

#ifndef HARPIA_DEBUG
#define DebugLog(args...)
#define DebugLogWarning(args...)
#define DebugLogError(args...)
#else //HARPIA_DEBUG

#include "String.h"

#ifdef __MINGW32__

inline std::string DebugCallerName(const std::string &s) {
    size_t end = s.find("(");
    size_t begin = s.find("::") + 2;
    size_t size = end - begin;
    return s.substr(begin, size);
}

#define HARPIA_CALLER DebugCallerName(__PRETTY_FUNCTION__).c_str()
#else //__MINGW32__
#define HARPIA_CALLER __func__
#endif //__MINGW32__

namespace Harpia {
    class Debug {
    public:
        static void Log(const char *tag, const char *message);

        static void LogWarning(const char *tag, const char *message);

        static void LogError(const char *tag, const char *message);

        template<typename... Args>
        static void Log(const char *tag, const char *format, Args ... args) {
            Log(tag, String::Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogWarning(const char *tag, const char *format, Args ... args) {
            LogWarning(tag, String::Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogError(const char *tag, const char *format, Args ... args) {
            LogError(tag, String::Format(format, args...).c_str());
        }
    };
}

#define DebugLog(args...) do{Harpia::Debug::Log(HARPIA_CALLER,args);}while(0)
#define DebugLogWarning(args...) do{Harpia::Debug::LogWarning(HARPIA_CALLER,args);}while(0)
#define DebugLogError(args...) do{Harpia::Debug::LogError(HARPIA_CALLER,args);}while(0)

#endif //HARPIA_DEBUG
#endif //HARPIAGAMEENGINE_DEBUG_H
