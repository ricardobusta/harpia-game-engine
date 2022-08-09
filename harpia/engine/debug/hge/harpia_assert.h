//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/06/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIA_ASSERT_H
#define HARPIAGAMEENGINE_HARPIA_ASSERT_H

#include "debug.h"

#ifndef HARPIA_DEBUG
#define Assert(condition) (void(0))
#define AssertNotNull(condition, args...) (void(0))
#else//HARPIA_DEBUG

#include <cassert>

#define AssertThat(condition, args...) Harpia::Assert::That(condition, HARPIA_CALLER, __FILE__, __LINE__, Harpia::Debug::Format(args).c_str())
#define AssertNotNull(condition, args...) AssertThat((condition) != nullptr, "%s is nullptr", #condition)

namespace Harpia {
    class Assert {
    public:
        static void That(bool condition, const char *caller, const char *file, int line, const char *message);

        template<typename T>
        static void NotNull(T *target, const char *targetName, const char *caller, const char *file, int line,
                            const char *message){
            That(target != nullptr, caller, file, line,
                 Harpia::Debug::Format("%s is nullptr. %s", targetName, message).c_str());
        }
    };
}// namespace Harpia

#endif//HARPIA_DEBUG

#endif//HARPIAGAMEENGINE_HARPIA_ASSERT_H
