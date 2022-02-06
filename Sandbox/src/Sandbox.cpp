//
// Created by Htrap19 on 12/6/21.
//

#include "Sandbox.h"

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <ImGuizmo.h>

#include "Freesia/Core/Application.h"

#include "Freesia/Scene/SceneSerializer.h"

#include "Freesia/Math/Math.h"

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

    m_SceneHierarchyPanel.SetContext(m_Scene);
}

void Sandbox::OnEvent(Freesia::Event& e)
{
    m_EditorCamera.OnEvent(e);

    Freesia::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Freesia::KeyPressedEvent>(FS_BIND_EVENT_FN(Sandbox::OnKeyPressed));
}

void Sandbox::OnUpdate(Freesia::TimeStep ts)
{
    // Resize framebuffer
    if (Freesia::FrameBufferSpecification spec = m_FrameBuffer->GetSpecification();
        m_Viewport.x > 0.0f && m_Viewport.y > 0.0f &&
        (spec.Width != (uint32_t)m_Viewport.x || spec.Height != (uint32_t)m_Viewport.y))
    {
        m_FrameBuffer->Resize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
        m_EditorCamera.SetViewportSize(m_Viewport.x, m_Viewport.y);
        m_Scene->OnViewportResize((uint32_t)m_Viewport.x, (uint32_t)m_Viewport.y);
    }

    if (m_ViewportFocused)
        m_EditorCamera.OnUpdate(ts);

    m_FrameBuffer->Bind();
    Freesia::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    Freesia::RenderCommand::Clear();

//    m_Scene->OnUpdateRuntime(ts);
    m_Scene->OnUpdateEditor(m_EditorCamera, ts);

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

            if (ImGui::MenuItem("Serialize"))
            {
                Freesia::SceneSerializer serializer(m_Scene);
                serializer.Serialize("assets/scenes/Example.freesia");
            }

            if (ImGui::MenuItem("Deserialize"))
            {
                Freesia::SceneSerializer serializer(m_Scene);
                serializer.Deserialize("assets/scenes/Example.freesia");
            }

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
    Freesia::Application::Get().GetImGuiLayer().SetBlockEvent(!m_ViewportFocused && !m_ViewportHovered);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    m_Viewport = { viewportPanelSize.x, viewportPanelSize.y };

    uint64_t textureID = m_FrameBuffer->GetColorAttachmentRendererID();
    ImGui::Image(reinterpret_cast<void*>(textureID), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

    Freesia::Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
    if (selectedEntity && m_GizmoType != -1)
    {
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();

        auto windowWidth = (float)ImGui::GetWindowWidth();
        auto windowHeight = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

        // Runtime camera from entity
//        // Camera
//        auto cameraEntity = m_Scene->GetPrimaryCameraEntity();
//        const auto& camera = cameraEntity.GetComponent<Freesia::CameraComponent>().Camera;
//
//        const glm::mat4& cameraProjection = camera.GetProjection();
//        glm::mat4 cameraView = camera.GetViewMatrix();

        // Editor camera
        const glm::mat4& cameraProjection = m_EditorCamera.GetProjection();
        glm::mat4 cameraView = m_EditorCamera.GetViewMatrix();

        // Entity transform
        auto& tc = selectedEntity.GetComponent<Freesia::TransformComponent>();
        glm::mat4 transform = tc.GetTransform();

        // Snapping
        bool snap = Freesia::Input::IsKeyPressed(Freesia::Key::LeftControl);
        float snapValue = 0.5f; // Snap value for translation/scale
        // Snap 45.0f degrees for rotation
        if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
            snapValue = 45.0f;

        float snapValues[3] = { snapValue, snapValue, snapValue };

        ImGuizmo::Manipulate(glm::value_ptr(cameraView),
                             glm::value_ptr(cameraProjection),
                             (ImGuizmo::OPERATION)m_GizmoType,
                             ImGuizmo::LOCAL,
                             glm::value_ptr(transform),
                             nullptr,
                             snap ? snapValues : nullptr);

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 translation, rotation, scale;
            Freesia::Math::DecomposeTransform(transform, translation, rotation, scale);

            glm::vec3 deltaRotation = rotation - tc.Rotation;
            tc.Translation = translation;
            tc.Rotation += deltaRotation;
            tc.Scale = scale;
        }
    }

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

bool Sandbox::OnKeyPressed(Freesia::KeyPressedEvent& e)
{
    if (e.GetRepeatCount() > 0)
        return false;

    switch(e.GetKeyCode())
    {
        case Freesia::Key::Q: m_GizmoType = -1;
            break;
        case Freesia::Key::W: m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            break;
        case Freesia::Key::E: m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            break;
        case Freesia::Key::R: m_GizmoType = ImGuizmo::OPERATION::SCALE;
            break;

        default:
            break;
    }

    return false;
}
