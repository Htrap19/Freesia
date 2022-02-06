//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_SANDBOX_H
#define FREESIA_SANDBOX_H

#include <Freesia.h>
#include "Panels/SceneHierarchyPanel.h"

#include "Freesia/Renderer/EditorCamera.h"

class Sandbox : public Freesia::Layer
{
public:
    Sandbox();

    void OnAttach() override;
    void OnEvent(Freesia::Event& e) override;
    void OnUpdate(Freesia::TimeStep ts) override;
    void OnImGuiRender() override;

protected:
    bool OnKeyPressed(Freesia::KeyPressedEvent& e);

private:
    // Required
    Freesia::Ref<Freesia::FrameBuffer> m_FrameBuffer;
    Freesia::SceneHierarchyPanel m_SceneHierarchyPanel;

    Freesia::Ref<Freesia::Scene> m_Scene;
    Freesia::Entity m_Camera;
    Freesia::Entity m_StyledChest;

    Freesia::EditorCamera m_EditorCamera;

    int32_t m_GizmoType = -1;

    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_Viewport = { 0.0f, 0.0f };
};

#endif //FREESIA_SANDBOX_H
