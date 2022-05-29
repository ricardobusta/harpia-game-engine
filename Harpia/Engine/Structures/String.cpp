//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "String.h"

#include <utility>

namespace Harpia::Engine {
    String &String::operator=(const std::string &s) {
        _string = s;
        return *this;
    }

    bool String::operator==(const std::string &s) const {
        return _string == s;
    }

    bool String::operator==(String s) const {
        return _string == s._string;
    }

    const char *String::ToCString() const {
        return _string.c_str();
    }

    std::string String::StdString() const {
        return _string;
    }

    String::operator std::string() const {
        return _string;
    }

    std::ostream &operator<<(std::ostream &s, const String &string) {
        return s << string.StdString();
    }
}
