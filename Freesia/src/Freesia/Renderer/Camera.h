//
// Created by htrap19 on 12/19/21.
//

#ifndef FREESIA_CAMERA_H
#define FREESIA_CAMERA_H

#include <glm/glm.hpp>

namespace Freesia
{
    class Camera
    {
    public:
        Camera() = default;
        explicit Camera(const glm::mat4& projection)
            : m_Projection(projection)
        {}
        virtual ~Camera() = default;

        inline const glm::mat4& GetProjection() const { return m_Projection; }
        virtual glm::mat4 GetViewMatrix() const = 0;

    protected:
        glm::mat4 m_Projection = glm::mat4(1.0f);
    };
}

#endif //FREESIA_CAMERA_H
