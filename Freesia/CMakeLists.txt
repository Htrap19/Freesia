find_package( Threads )
add_subdirectory(vendor)

file(GLOB_RECURSE sources src/*.cpp)

add_library(Freesia STATIC ${sources} vendor/glad/src/glad.c vendor/stb_image/stb_image.cpp)
target_include_directories(Freesia PRIVATE src vendor/glfw/include vendor/spdlog/include vendor/glad/include vendor/entt/include vendor/glm/ vendor/stb_image vendor/imgui)
target_link_libraries(Freesia PRIVATE glfw imgui Threads::Threads)