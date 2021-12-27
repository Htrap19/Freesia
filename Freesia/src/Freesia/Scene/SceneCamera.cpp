//
// Created by htrap19 on 12/19/21.
//

#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

namespace Freesia
{
    SceneCamera::SceneCamera()
    {
        RecalculateView();
    }

    void SceneCamera::SetOrthoGraphic(float size, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::OrthoGraphic;
        m_OrthoGraphicSize = size;
        m_OrthoGraphicNearClip = nearClip;
        m_OrthoGraphicFarClip = farClip;

        RecalculateView();
    }

    void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
    {
        m_ProjectionType = ProjectionType::Perspective;
        m_PerspectiveFOV = verticalFOV;
        m_PerspectiveNearClip = nearClip;
        m_PerspectiveFarClip = farClip;

        RecalculateView();
    }

    void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
    {
        m_AspectRatio = (float)width / (float)height;
        RecalculateView();
    }

    void SceneCamera::RecalculateView()
    {
        if (m_ProjectionType == ProjectionType::Perspective)
            m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNearClip, m_PerspectiveFarClip);
        else
        {
            float orthoLeft = -m_OrthoGraphicSize * m_AspectRatio * 0.5f;
            float orthoRight = m_OrthoGraphicSize * m_AspectRatio * 0.5f;
            float orthoBottom = -m_OrthoGraphicSize * 0.5f;
            float orthoUp = m_OrthoGraphicSize * 0.5f;

            m_Projection = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoUp, m_OrthoGraphicNearClip, m_OrthoGraphicFarClip);
        }
    }

    glm::mat4 SceneCamera::GetView() const
    {
        if (m_ProjectionType == ProjectionType::Perspective)
            return glm::lookAt(glm::vec3(0.0f, 2.0f, -5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        return glm::mat4(1.0f);
    }
}