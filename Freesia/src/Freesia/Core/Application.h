//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_APPLICATION_H
#define FREESIA_APPLICATION_H

namespace Freesia
{
    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
    };

    Application* CreateApplication();
}

#endif //FREESIA_APPLICATION_H
