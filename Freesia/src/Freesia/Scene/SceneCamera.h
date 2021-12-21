//
// Created by htrap19 on 12/19/21.
//

#ifndef FREESIA_SCENECAMERA_H
#define FREESIA_SCENECAMERA_H

#include "Freesia/Renderer/Camera.h"

namespace Freesia
{
    class SceneCamera : public Camera
    {
    public:
        enum class ProjectionType { Perspective = 0, OrthoGraphic = 1 };
        bool IsPrimary = true, FixedAspectRatio = false;

    public:
        SceneCamera();
        ~SceneCamera() override = default;

        void SetOrthoGraphic(float size, float nearClip, float farClip);
        void SetPerspective(float verticalFOV, float nearClip, float farClip);

        void SetViewportSize(uint32_t width, uint32_t height);

        inline void SetProjectionType(ProjectionType type) { m_ProjectionType = type; }
        inline const ProjectionType GetProjectionType() const { return m_ProjectionType; }

        inline void SetOrthoGraphicSize(float size) { m_OrthoGraphicSize = size; }
        inline float GetOrthoGraphicSize() const { return m_OrthoGraphicSize; }

        inline void SetOrthoGraphicNearClip(float clip) { m_OrthoGraphicNearClip = clip; }
        inline float GetOrthoGraphicNearClip() const { return m_OrthoGraphicNearClip; }

        inline void SetOrthoGraphicFarClip(float clip) { m_OrthoGraphicFarClip = clip; }
        inline float GetOrthoGraphicFarClip() const { return m_OrthoGraphicFarClip; }

        inline void SetPerspectiveFOV(float fov) { m_PerspectiveFOV = fov; }
        inline float GetPerspectiveFOV() const { return m_PerspectiveFOV; }

        inline void SetPerspectiveNearClip(float clip) { m_PerspectiveNearClip = clip; }
        inline float GetPerspectiveNearClip() const { return m_PerspectiveNearClip; }

        inline void SetPerspectiveFarClip(float clip) { m_PerspectiveFarClip = clip; }
        inline float GetPerspectiveFarClip() const { return m_PerspectiveFarClip; }

        glm::mat4 GetView() const override;

    private:
        void RecalculateView();

    private:
        ProjectionType m_ProjectionType = ProjectionType::OrthoGraphic;

        // Orthographic Data
        float m_OrthoGraphicSize = 10.0f;
        float m_OrthoGraphicFarClip = 1.0f, m_OrthoGraphicNearClip = -1.0f;

        // Perspective Data
        float m_PerspectiveFOV = glm::radians(45.0f);
        float m_PerspectiveFarClip = 1000.0f, m_PerspectiveNearClip = 0.01f;

        float m_AspectRatio = 0.0f;
    };
}

#endif //FREESIA_SCENECAMERA_H
