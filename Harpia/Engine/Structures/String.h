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
        [[nodiscard]] const char *ToCString() const;

        String &operator=(const std::string &s);

        bool operator==(const std::string &s) const;

        bool operator==(String s) const;

        explicit operator std::string() const;

        [[nodiscard]] std::string StdString() const;
    };

    std::ostream &operator<<(std::ostream &s, const String &string);
}

#endif //HARPIAGAMEENGINE_STRING_H
