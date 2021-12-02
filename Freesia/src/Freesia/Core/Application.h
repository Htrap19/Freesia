//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_APPLICATION_H
#define FREESIA_APPLICATION_H

#include <Freesia/Core/Window.h>

namespace Freesia
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();

    private:
        Scope<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
}

#endif //FREESIA_APPLICATION_H
