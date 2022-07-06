//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "harpia_string.h"

namespace Harpia {
    std::string String::ReadFile(const std::string &path, bool * ok) {
        std::ifstream t(path);

        if(t.fail()){
            *ok = false;
            return {};
        }

        t.seekg(0, std::ios::end);
        size_t size = t.tellg();
        std::string buffer(size, ' ');
        t.seekg(0);
        t.read(&buffer[0], size);
        *ok = true;
        return buffer;
    }
}
