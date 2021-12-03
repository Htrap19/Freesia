//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_CORE_H
#define FREESIA_CORE_H

#include <memory>

#ifdef FS_DEBUG
    #ifdef FS_PLATFORM_UNIX
        #include <csignal>
        #define FS_DEBUGBREAK() raise(SIGTRAP)
    #elif FS_PLATFORM_WINDOWS
        #define FS_DEBUGBREAK() __debugbreak();
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
#else
    #define FS_DEBUGBREAK()
#endif

#define BIT(x) (1 << x)
#define FS_EXPAND_MACRO(x) x
#define FS_STRINGIFY_MACRO(x) #x

#define FS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Freesia
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif //FREESIA_CORE_H
