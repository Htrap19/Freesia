//
// Created by Htrap19 on 12/1/21.
//

#include "Window.h"
#ifdef FS_PLATFORM_UNIX
    #include "Platform/X11/X11Window.h"
#endif

namespace Freesia
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
        return CreateScope<X11Window>(props);
    }
}