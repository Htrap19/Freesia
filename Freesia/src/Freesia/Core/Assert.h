//
// Created by Htrap19 on 12/3/21.
//

#ifndef FREESIA_ASSERT_H
#define FREESIA_ASSERT_H

#include "Freesia/Core/Core.h"
#include "Freesia/Core/Log.h"

namespace Freesia::Assert
{
    constexpr const char* GetCurrentFileName(const char* path)
    {
        const char* file = path;
        while (*path)
        {
            if (*path == '/' || *path == '\\')
                file = ++path;
            else
                path++;
        }

        return file;
    }
}

#ifdef FS_ENABLE_ASSERT

    #define FS_INTERNAL_ASSERT_IMPL(type, check, msg, ...) if (!(check)) { FS##type##ERROR(msg, __VA_ARGS__); FS_DEBUGBREAK(); }
    #define FS_INTERNAL_ASSERT_WITH_MSG(type, check, ...) FS_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define FS_INTERNAL_ASSERT_NO_MSG(type, check) FS_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", FS_STRINGIFY_MACRO(check), ::Freesia::Assert::GetCurrentFileName(__FILE__), __LINE__)

    // E.G
    //                check       msg
    // FS_CORE_ASSERT(false, "Why failed!")
    #define FS_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define FS_INTERNAL_ASSERT_GET_MACRO(...)  FS_EXPAND_MACRO( FS_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, FS_INTERNAL_ASSERT_WITH_MSG, FS_INTERNAL_ASSERT_NO_MSG) )

    #define FS_ASSERT(...) FS_EXPAND_MACRO( FS_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define FS_CORE_ASSERT(...) FS_EXPAND_MACRO( FS_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else
    #define FS_ASSERT(...)
    #define FS_CORE_ASSERT(...)

#endif

#endif //FREESIA_ASSERT_H
