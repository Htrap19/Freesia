//
// Created by htrap19 on 2/3/22.
//

#ifndef FREESIA_MATH_H
#define FREESIA_MATH_H

#include <glm/glm.hpp>

namespace Freesia::Math
{
    bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
}

#endif //FREESIA_MATH_H
