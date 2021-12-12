//
// Created by Htrap19 on 12/6/21.
//

#include "Sandbox.h"

#include <imgui.h>

Sandbox::Sandbox()
    : Freesia::Layer("Sandbox")
{
}

void Sandbox::OnAttach()
{
    m_VAO = Freesia::VertexArray::Create();
    m_Shader = Freesia::Shader::Create("assets/shaders/Model3D.glsl");

    float vertices[] =
    {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
    };

    uint32_t indices[] = { 0, 1, 2 };

    auto vbo = Freesia::VertexBuffer::Create(vertices, sizeof(vertices));
    vbo->SetLayout({
        { Freesia::ShaderDataType::Float3, "a_Position" }
    });
    auto ibo = Freesia::IndexBuffer::Create(indices, 3);

    m_VAO->AddVertexBuffer(vbo);
    m_VAO->SetIndexBuffer(ibo);
}

void Sandbox::OnUpdate(Freesia::TimeStep ts)
{
    Freesia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Freesia::RenderCommand::Clear();

    m_Shader->Bind();
    Freesia::RenderCommand::DrawIndexed(m_VAO);
}

void Sandbox::OnImGuiRender()
{
    ImGui::Begin("Hello World");
    ImGui::Text("Hello to Dear ImGui");
    ImGui::End();
}
