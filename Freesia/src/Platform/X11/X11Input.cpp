//
// Created by Htrap19 on 12/6/21.
//

#include <GLFW/glfw3.h>

#include "Freesia/Core/Input.h"
#include "Freesia/Core/Application.h"

#ifdef FS_PLATFORM_UNIX
namespace Freesia
{
    bool Input::IsKeyPressed(KeyCode key)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(MouseCode button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    glm::vec2 Input::GetCursorPosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return { (float)xpos, (float)ypos };
    }

    float Input::GetCursorX()
    {
        return Input::GetCursorPosition().x;
    }

    float Input::GetCursorY()
    {
        return Input::GetCursorPosition().y;
    }
}
#endif