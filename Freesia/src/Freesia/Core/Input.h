//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_INPUT_H
#define FREESIA_INPUT_H

#include <glm/glm.hpp>

#include "Freesia/Core/KeyCodes.h"
#include "Freesia/Core/MouseCodes.h"

namespace Freesia
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetCursorPosition();
        static float GetCursorX();
        static float GetCursorY();
    };
}

#endif //FREESIA_INPUT_H
