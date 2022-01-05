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

    m_Scene = Freesia::CreateRef<Freesia::Scene>();

    m_Camera = m_Scene->CreateEntity("Camera");
    m_Camera.AddComponent<Freesia::CameraComponent>().Camera.SetProjectionType(Freesia::SceneCamera::ProjectionType::Perspective);

    m_StyledChest = m_Scene->CreateEntity("Chest");
    m_StyledChest.AddComponent<Freesia::MeshComponent>("assets/models/stylized_treasure_chest/scene.gltf");
    m_StyledChest.GetComponent<Freesia::TransformComponent>().Scale = glm::vec3(0.020f);

    class ModelController : public Freesia::ScriptableEntity
    {
    public:
        void OnCreate() override
        {}

        void OnDestroy() override
        {}

        void OnUpdate(Freesia::TimeStep ts) override
        {
            if (!HasComponent<Freesia::TransformComponent>()) return;

            auto y = glm::radians(ts * m_Speed);

            auto& transComp = GetComponent<Freesia::TransformComponent>();
            transComp.Rotation.y += y;
            if (glm::degrees(transComp.Rotation.y) >= 360.0f)
                transComp.Rotation.y = 0;
        }

    private:
        const float m_Speed = 50.0f;
    };
    m_StyledChest.AddComponent<Freesia::NativeScriptComponent>().Bind<ModelController>();

    m_SceneHierarchyPanel.SetContext(m_Scene);
}

void Sandbox::OnUpdate(Freesia::TimeStep ts)
{
    // Resize framebuffer
    if (Freesia::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
        m_Viewport.x > 0.0f && m_Viewport.y > 0.0f &&
        (spec.Width != (uint32_t)m_Viewport.x || spec.Height != (uint32_t)m_Viewport.y))
    {
        m_FrameBuffer->Resize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
        m_Scene->OnViewportResize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
    }

    m_FrameBuffer->Bind();
    Freesia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Freesia::RenderCommand::Clear();

    m_Scene->OnUpdate(ts);

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
    auto boldFont = io.Fonts->Fonts[0];
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

    m_SceneHierarchyPanel.OnImGuiRender();

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

    ImGui::Begin("Stats");
    auto stats = Freesia::Renderer::GetStats();
    ImGui::Text("Renderer Stats:");
    ImGui::Separator();
    ImGui::PushFont(boldFont);
    ImGui::Text("Draw calls: %d", stats.DrawCalls);
    ImGui::Text("Mesh count: %d", stats.MeshCount);
    ImGui::Text("Vertices: %d", stats.TotalVertices);
    ImGui::Text("Indices: %d", stats.TotalIndices);
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::PopFont();
    ImGui::End();

    ImGui::End();
}
