cmake_minimum_required(VERSION 3.20)
project(Freesia)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Freesia/vendor)
set(LINK_ARGS "-lpthread -ldl")

include_directories(Freesia/src Freesia/vendor/glfw/include)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${LINK_ARGS})
add_executable(Sandbox Sandbox/src/SandboxApp.cpp Freesia/src/Freesia/Core/EntryPoint.h Freesia/src/Freesia/Core/Application.cpp Freesia/src/Freesia/Core/Application.h Freesia/src/Freesia.h Freesia/src/Freesia/Core/Core.h Freesia/src/Freesia/Core/Window.cpp Freesia/src/Freesia/Core/Window.h Freesia/src/Platform/X11/X11Window.cpp Freesia/src/Platform/X11/X11Window.h Freesia/src/Freesia/Events/Event.h Freesia/src/Freesia/Events/WindowEvent.h Freesia/src/Freesia/Events/KeyEvent.h Freesia/src/Freesia/Core/KeyCodes.h Freesia/src/Freesia/Core/MouseCodes.h Freesia/src/Freesia/Events/MouseEvent.h)
target_link_libraries(Sandbox PUBLIC glfw)
