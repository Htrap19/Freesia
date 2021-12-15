//
// Created by Htrap19 on 12/6/21.
//

#include "Sandbox.h"

#include <imgui.h>

#include "Freesia/Core/Application.h"

Sandbox::Sandbox()
    : Freesia::Layer("Sandbox")
{
}

void Sandbox::OnAttach()
{
    auto& app = Freesia::Application::Get();
    Freesia::FrameBufferSpecification spec;
    spec.Width = app.GetWindow().GetWidth();
    spec.Height = app.GetWindow().GetHeight();
    m_FrameBuffer = Freesia::FrameBuffer::Create(spec);

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
    // Resize framebuffer
    if (Freesia::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
        m_Viewport.x > 0.0f && m_Viewport.y > 0.0f &&
        (spec.Width != (uint32_t)m_Viewport.x || spec.Height != (uint32_t)m_Viewport.y))
        m_FrameBuffer->Resize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);

    m_FrameBuffer->Bind();
    Freesia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Freesia::RenderCommand::Clear();

    m_Shader->Bind();
    Freesia::RenderCommand::DrawIndexed(m_VAO);
    m_FrameBuffer->Unbind();
}

void Sandbox::OnImGuiRender()
{
    // Dockspace Window
    static bool dockSpaceOpen = true;
    static bool optFullscreenPersistant = true;
    bool optFullscreen = optFullscreenPersistant;
    static ImGuiDockNodeFlags dockSpaceFlags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags mainWindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (optFullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        mainWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        mainWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
        mainWindowFlags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Dockspace", &dockSpaceOpen, mainWindowFlags);
    ImGui::PopStyleVar();

    if (optFullscreen)
        ImGui::PopStyleVar(2);

    // Dockspace
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 330.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockSpaceID = ImGui::GetID("MyDockspace");
        ImGui::DockSpace(dockSpaceID, ImVec2(0.0f, 0.0f), dockSpaceFlags);
    }
    style.WindowMinSize.x = minWinSizeX;

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Freesia"))
        {
            if (ImGui::MenuItem("Exit")) Freesia::Application::Get().Close();

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    // Viewport
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("Viewport");

    m_ViewportFocused = ImGui::IsWindowFocused();
    m_ViewportHovered = ImGui::IsWindowHovered();
    Freesia::Application::Get().GetImGuiLayer().SetBlockEvent(!m_ViewportFocused || !m_ViewportHovered);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    m_Viewport = { viewportPanelSize.x, viewportPanelSize.y };

    uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
    ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();

    ImGui::Begin("Testing");
    ImGui::Text("Hello World");
    ImGui::Button("Click me");
    ImGui::End();

    ImGui::End();
}
