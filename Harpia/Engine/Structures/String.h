//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_STRING_H
#define HARPIAGAMEENGINE_STRING_H

#include <string>
#include <stdexcept>
#include <memory>
#include <iostream>

namespace Harpia::Engine {
    class String {
    public:
        template<typename ... Args>
        static std::string Format(const std::string &format, Args ... args);
    };

    template<typename ... Args>
    std::string String::Format(const std::string &format, Args ... args) {
        // Thanks https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
        int stringSize = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // Extra space for '\0'
        if (stringSize <= 0) { throw std::runtime_error("Error during formatting."); }
        auto size = static_cast<size_t>( stringSize );
        std::unique_ptr<char[]> buf(new char[size]);
        try {
            std::snprintf(buf.get(), size, format.c_str(), args...);
        }catch(char c) {
            std::runtime_error("Something went wrong. Maybe wrong type conversion.");
        }
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside NOLINT(modernize-return-braced-init-list)
    }
}

#endif //HARPIAGAMEENGINE_STRING_H
