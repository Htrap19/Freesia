//
// Created by Htrap19 on 12/1/21.
//

#include "Window.h"
#include "Platform/x11/X11Window.h"

namespace Freesia
{
    Scope<Window> Window::Create(const WindowProps& props)
    {
        return CreateScope<X11Window>(props);
    }
}