//
// Created by Htrap19 on 12/6/21.
//

#ifndef FREESIA_SANDBOX_H
#define FREESIA_SANDBOX_H

#include <Freesia.h>

class Sandbox : public Freesia::Layer
{
public:
    Sandbox();

    void OnAttach() override;
    void OnUpdate(Freesia::TimeStep ts) override;
    void OnImGuiRender() override;

private:
    Freesia::Ref<Freesia::VertexArray> m_VAO;
    Freesia::Ref<Freesia::Shader> m_Shader;

    Freesia::Ref<Freesia::FrameBuffer> m_FrameBuffer;

    bool m_ViewportFocused = false, m_ViewportHovered = false;
    glm::vec2 m_Viewport = { 0.0f, 0.0f };
};

#endif //FREESIA_SANDBOX_H
