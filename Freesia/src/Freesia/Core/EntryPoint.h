//
// Created by Htrap19 on 12/1/21.
//

#ifndef FREESIA_ENTRYPOINT_H
#define FREESIA_ENTRYPOINT_H

extern Freesia::Application* Freesia::CreateApplication();

int main(int argc, char* argv[])
{
    Freesia::Log::Init();

    auto app = Freesia::CreateApplication();
    app->Run();
    delete app;

    return 0;
}

#endif //FREESIA_ENTRYPOINT_H
