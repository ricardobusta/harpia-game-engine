//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 09/06/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIA_ASSERT_H
#define HARPIAGAMEENGINE_HARPIA_ASSERT_H

#ifndef HARPIA_DEBUG
#define Assert(condition) (void(0))
#define AssertNotNull(condition) (void(0))
#else //HARPIA_DEBUG

#include <cassert>
#include "Debug.h"

#define AssertThat(condition, args...) Harpia::Assert::That(condition,HARPIA_CALLER,__FILE__,__LINE__,Harpia::Debug::Format(args).c_str())
#define AssertNotNull(condition, args...) AssertThat((condition)!=nullptr,"%s is nullptr",#condition)

namespace Harpia {
    class Assert {
    public:
        static void That(bool condition, const char *caller, const char *file, const int line, const char *message);
        static void NotNull(void *target, const char *targetName, const char *caller, const char *file, const int line,
                            const char *message);
    };
}

#endif //HARPIA_DEBUG

#endif //HARPIAGAMEENGINE_HARPIA_ASSERT_H
