//
// Created by htrap19 on 2/6/22.
//

#ifndef FREESIA_EDITORCAMERA_H
#define FREESIA_EDITORCAMERA_H

#include "Freesia/Renderer/Camera.h"

#include "Freesia/Core/Timestep.h"

#include "Freesia/Events/MouseEvent.h"

#include <glm/glm.hpp>

namespace Freesia
{
    class EditorCamera : public Camera
    {
    public:
        EditorCamera() = default;
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void OnUpdate(TimeStep ts);
        void OnEvent(Event& e);

        inline float GetDistance() const { return m_Distance; }
        inline void SetDistance(float distance) { m_Distance = distance; }

        inline void SetViewportSize(float width, float height) { m_ViewportWidth = width, m_ViewportHeight = height; UpdateProjection(); }

        inline glm::mat4 GetViewMatrix() const override { return m_ViewMatrix; }
        inline glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

        glm::vec3 GetUpDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetForwardDirection() const;

        inline const glm::vec3& GetPosition() const { return m_Position; }
        glm::quat GetOrientation() const;

        inline float GetPitch() const { return m_Pitch; }
        inline float GetYaw() const { return m_Yaw; }

    private:
        void UpdateProjection();
        void UpdateView();

        bool OnMouseScroll(MouseScrolledEvent& e);

        void MousePan(const glm::vec2& delta);
        void MouseRotate(const glm::vec2& delta);
        void MouseZoom(float delta);

        glm::vec3 CalculatePosition() const;

        std::pair<float, float> PanSpeed() const;
        float RotateSpeed() const { return 0.8f; }
        float ZoomSpeed() const;

    private:
        float m_FOV = 45.0f, m_AspectRatio, m_NearClip = 0.1f, m_FarClip = 1000.0f;

        glm::mat4 m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

        glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

        float m_Distance = 10.0f, m_Yaw = 0.0f, m_Pitch = 0.0f;
        float m_ViewportWidth, m_ViewportHeight;
    };
}

#endif //FREESIA_EDITORCAMERA_H
