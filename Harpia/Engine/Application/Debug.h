//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_DEBUG_H
#define HARPIAGAMEENGINE_DEBUG_H

#include "String.h"

namespace Harpia::Engine {
    class Debug {
    public:
        static void Log(std::string msg){
            std::cout << msg << std::endl;
        }

        static void LogError(std::string msg){
            std::cerr << msg << std::endl;
        }

        template<typename... Args>
        static void Log(std::string format, Args ... args) {
            Log(String::Format(format, args...));
        }

        template<typename... Args>
        static void LogError(std::string format, Args ... args) {
            LogError(String::Format(format, args...));
        }
    };
}

#endif //HARPIAGAMEENGINE_DEBUG_H
