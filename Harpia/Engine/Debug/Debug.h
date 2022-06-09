//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_DEBUG_H
#define HARPIAGAMEENGINE_DEBUG_H

#ifndef HARPIA_DEBUG
#define DebugLog(args...) (void(0))
#define DebugLogWarning(args...) (void(0))
#define DebugLogError(args...) (void(0))
#else //HARPIA_DEBUG

#include <string>
#include <memory>
#include <stdexcept>

#ifdef __MINGW32__
#define HARPIA_CALLER Harpia::Debug::CallerName(__PRETTY_FUNCTION__).c_str()
#else //__MINGW32__
#define HARPIA_CALLER __func__
#endif //__MINGW32__

#define DebugLog(args...) do{Harpia::Debug::Log(HARPIA_CALLER,args);}while(0)
#define DebugLogWarning(args...) do{Harpia::Debug::LogWarning(HARPIA_CALLER,args);}while(0)
#define DebugLogError(args...) do{Harpia::Debug::LogError(HARPIA_CALLER,__FILE__,__LINE__,args);}while(0)

namespace Harpia {
    class Debug {
    public:
        static void Log(const char *tag, const char *message);

        static void LogWarning(const char *tag, const char *message);

        static void LogError(const char *tag, const char *file, int line, const char *message);

        template<typename... Args>
        static void Log(const char *tag, const char *format, Args ... args) {
            Log(tag, Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogWarning(const char *tag, const char *format, Args ... args) {
            LogWarning(tag, Format(format, args...).c_str());
        }

        template<typename... Args>
        static void LogError(const char *tag, const char *file, int line, const char *format, Args ... args) {
            LogError(tag, file, line, Format(format, args...).c_str());
        }

        static std::string CallerName(const std::string &s);

    public:
        template<typename... Args>
        static std::string Format(const char *format) {
            return std::string(format); // We don't want the '\0' inside
        }

        template<typename... Args>
        static std::string Format(const char *format, Args ... args) {
            // Thanks https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
            int stringSize = std::snprintf(nullptr, 0, format, args...) + 1; // Extra space for '\0'
            if (stringSize <= 0) { throw std::runtime_error("Error during formatting."); }
            auto size = static_cast<size_t>( stringSize );
            std::unique_ptr<char[]> buf(new char[size]);
            std::snprintf(buf.get(), size, format, args...);
            return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
        }
    };
}

#endif //HARPIA_DEBUG
#endif //HARPIAGAMEENGINE_DEBUG_H
