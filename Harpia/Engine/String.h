//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_STRING_H
#define HARPIAGAMEENGINE_STRING_H

#include <string>

namespace Harpia::Engine {
    class String {
    private:
        std::string _string;
    public:
        const char* ToCString();

        String &operator=(const std::string& s);
        bool operator==(const std::string& s);
        bool operator==(String s);
    };
}

#endif //HARPIAGAMEENGINE_STRING_H
