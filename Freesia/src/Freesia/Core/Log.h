//
// Created by Htrap19 on 12/3/21.
//

#ifndef FREESIA_LOG_H
#define FREESIA_LOG_H

#include "Freesia/Core/Core.h"
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Freesia
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
        static Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
    };
}

#define FS_CORE_ERROR(...)      ::Freesia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FS_CORE_WARN(...)       ::Freesia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FS_CORE_INFO(...)       ::Freesia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FS_CORE_TRACE(...)      ::Freesia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FS_CORE_CRITICAL(...)   ::Freesia::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define FS_ERROR(...)           ::Freesia::Log::GetClientLogger()->error(__VA_ARGS__)
#define FS_WARN(...)            ::Freesia::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FS_INFO(...)            ::Freesia::Log::GetClientLogger()->info(__VA_ARGS__)
#define FS_TRACE(...)           ::Freesia::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FS_CRITICAL(...)        ::Freesia::Log::GetClientLogger()->critical(__VA_ARGS__)

#endif //FREESIA_LOG_H
