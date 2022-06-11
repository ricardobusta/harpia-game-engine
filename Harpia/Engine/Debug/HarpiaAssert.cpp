//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/06/2022.
//

#include "HarpiaAssert.h"
#include <cassert>

namespace Harpia{
    void Assert::That(bool condition, const char *caller, const char *file, const int line, const char *message) {
        if (!condition) {
            Harpia::Debug::LogError(caller, file, line, message);
        }
        assert(condition);
    }

    void Assert::NotNull(void *target, const char * targetName, const char *caller, const char *file, const int line, const char *message) {
        auto condition = target != nullptr;
        That(target!= nullptr, caller, file, line, Harpia::Debug::Format("%s is nullptr. %s", targetName, message).c_str());
    }
}