add_compile_definitions(_GLFW_X11)

add_library(glfw STATIC
                glfw/src/context.c
                glfw/src/init.c
                glfw/src/input.c
                glfw/src/monitor.c
                glfw/src/vulkan.c
                glfw/src/window.c
                glfw/src/platform.c
                glfw/src/x11_init.c
                glfw/src/x11_monitor.c
                glfw/src/x11_window.c
                glfw/src/xkb_unicode.c
                glfw/src/posix_time.c
                glfw/src/posix_thread.c
                glfw/src/posix_module.c
                glfw/src/glx_context.c
                glfw/src/egl_context.c
                glfw/src/osmesa_context.c
                glfw/src/linux_joystick.c
                glfw/src/null_init.c
                glfw/src/null_monitor.c
                glfw/src/null_window.c
                glfw/src/null_joystick.c)
target_include_directories(glfw PUBLIC glfw/include glfw/src)