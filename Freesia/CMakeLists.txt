file(GLOB_RECURSE sources src/*.cpp)

add_library(Freesia STATIC ${sources} vendor/glad/src/glad.c vendor/stb_image/stb_image.cpp)
target_include_directories(Freesia PUBLIC src vendor/glfw/include vendor/spdlog/include vendor/glad/include vendor/entt/include vendor/glm/ vendor/stb_image)