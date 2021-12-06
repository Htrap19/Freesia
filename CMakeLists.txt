cmake_minimum_required(VERSION 3.20)
project(Freesia)
set(CMAKE_CXX_STANDARD 17)

find_package( Threads )

if (UNIX)
    add_definitions(-DFS_PLATFORM_UNIX)
    set(LINK_ARGS "-ldl")
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${LINK_ARGS})
elseif(WIN32)
    add_definitions(-DFS_PLATFORM_WINDOWS)
endif()

add_subdirectory(Freesia/vendor)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DFS_ENABLE_ASSERT -DFS_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DFS_RELEASE)
endif()

include_directories(Freesia/src Freesia/vendor/glfw/include Freesia/vendor/spdlog/include Freesia/vendor/glad/include Freesia/vendor/entt/include Freesia/vendor/glm/)

add_executable(Sandbox Freesia/vendor/glad/src/glad.c Sandbox/src/SandboxApp.cpp Freesia/src/Freesia/Core/EntryPoint.h Freesia/src/Freesia/Core/Application.cpp Freesia/src/Freesia/Core/Application.h Freesia/src/Freesia.h Freesia/src/Freesia/Core/Core.h Freesia/src/Freesia/Core/Window.cpp Freesia/src/Freesia/Core/Window.h Freesia/src/Platform/X11/X11Window.cpp Freesia/src/Platform/X11/X11Window.h Freesia/src/Freesia/Events/Event.h Freesia/src/Freesia/Events/WindowEvent.h Freesia/src/Freesia/Events/KeyEvent.h Freesia/src/Freesia/Core/KeyCodes.h Freesia/src/Freesia/Core/MouseCodes.h Freesia/src/Freesia/Events/MouseEvent.h Freesia/src/Freesia/Core/Assert.h Freesia/src/Freesia/Core/Log.h Freesia/src/Freesia/Core/Log.cpp Freesia/src/Freesia/Core/Layer.h Freesia/src/Freesia/Core/Timestep.h Freesia/src/Freesia/Core/LayerStack.cpp Freesia/src/Freesia/Core/LayerStack.h Freesia/src/Freesia/Renderer/GraphicsContext.cpp Freesia/src/Freesia/Renderer/GraphicsContext.h Freesia/src/Platform/OpenGL/OpenGLContext.cpp Freesia/src/Platform/OpenGL/OpenGLContext.h Freesia/src/Freesia/Renderer/RendererAPI.cpp Freesia/src/Freesia/Renderer/RendererAPI.h Freesia/src/Platform/OpenGL/OpenGLRendererAPI.cpp Freesia/src/Platform/OpenGL/OpenGLRendererAPI.h Freesia/src/Freesia/Renderer/RenderCommand.cpp Freesia/src/Freesia/Renderer/RenderCommand.h Freesia/src/Freesia/Renderer/Renderer.cpp Freesia/src/Freesia/Renderer/Renderer.h Sandbox/src/Sandbox.cpp Sandbox/src/Sandbox.h)
target_link_libraries(Sandbox PUBLIC glfw Threads::Threads)
