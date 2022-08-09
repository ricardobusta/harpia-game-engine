//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/06/2022.
//

#include "harpia_assert.h"
#include <cassert>

#ifdef HARPIA_DEBUG
namespace Harpia {
    void Assert::That(bool condition, const char *caller, const char *file, const int line, const char *message) {
        if (!condition) {
            Harpia::Debug::LogError(caller, file, line, message);
        }
        assert(condition);
    }
}// namespace Harpia
#endif//HARPIA_DEBUG