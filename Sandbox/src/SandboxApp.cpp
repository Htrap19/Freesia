#include <Freesia.h>
#include <Freesia/Core/EntryPoint.h>

class SandboxApp : public Freesia::Application
{
public:
    SandboxApp() = default;
};

Freesia::Application* Freesia::CreateApplication()
{
    return new SandboxApp();
}