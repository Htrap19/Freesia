//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_CORE_H
#define FREESIA_CORE_H

#include <memory>

#define BIT(x) (1 << x)

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
