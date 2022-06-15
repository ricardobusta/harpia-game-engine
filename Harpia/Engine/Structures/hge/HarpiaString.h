//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIASTRING_H
#define HARPIAGAMEENGINE_HARPIASTRING_H

#include <string>
#include <stdexcept>
#include <memory>

namespace Harpia {
    class String {
    public:
        template<typename ... Args>
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

#endif //HARPIAGAMEENGINE_HARPIASTRING_H
