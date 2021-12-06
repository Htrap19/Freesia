#include <Freesia.h>
#include <Freesia/Core/EntryPoint.h>

#include "Sandbox.h"

class SandboxApp : public Freesia::Application
{
public:
    SandboxApp()
    {
        PushLayer(new Sandbox);
    }
};

Freesia::Application* Freesia::CreateApplication()
{
    return new SandboxApp();
}