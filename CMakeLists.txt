cmake_minimum_required(VERSION 3.20)
project(Freesia)
set(CMAKE_CXX_STANDARD 17)

if (UNIX)
    add_definitions(-DFS_PLATFORM_UNIX)
    set(LINK_ARGS "-ldl")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${LINK_ARGS})
elseif(WIN32)
    add_definitions(-DFS_PLATFORM_WINDOWS)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DFS_ENABLE_ASSERT -DFS_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DFS_RELEASE)
endif()

add_subdirectory(Freesia)

add_executable(Sandbox Sandbox/src/SandboxApp.cpp Sandbox/src/Sandbox.cpp Sandbox/src/Sandbox.h)
target_include_directories(Sandbox PUBLIC Freesia/src Freesia/vendor/glm Freesia/vendor/spdlog/include Freesia/vendor/imgui)
target_link_libraries(Sandbox PUBLIC Freesia)
