//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "String.h"

#include <utility>

namespace Harpia::Engine {
    String &String::operator=(const std::string& s) {
        _string = s;
        return *this;
    }

    bool String::operator==(const std::string& s){
        return _string == s;
    }
    bool String::operator==(String s){
        return _string == s._string;
    }

    const char *String::ToCString() {
        return _string.c_str();
    }
}