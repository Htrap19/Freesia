find_package( Threads )
add_subdirectory(vendor)

file(GLOB_RECURSE sources src/*.cpp src/*.h)

add_library(Freesia STATIC ${sources} vendor/glad/src/glad.c vendor/stb_image/stb_image.cpp)
target_include_directories(Freesia PUBLIC src vendor/glfw/include vendor/spdlog/include vendor/glad/include vendor/entt/include vendor/glm/ vendor/stb_image vendor/imgui vendor/assimp/include vendor/yaml_cpp/include vendor/imguizmo)
target_link_libraries(Freesia PRIVATE glfw imgui assimp yaml_cpp imguizmo Threads::Threads)