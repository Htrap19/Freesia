cmake_minimum_required(VERSION 3.20)
project(Freesia)

set(CMAKE_CXX_STANDARD 17)
include_directories("Freesia/src")

add_executable(Freesia Sandbox/src/SandboxApp.cpp Freesia/src/Freesia/Core/EntryPoint.h Freesia/src/Freesia/Core/Application.cpp Freesia/src/Freesia/Core/Application.h Freesia/src/Freesia.h)
