//
// Created by htrap19 on 12/18/21.
//

#include "Scene.h"

#include "Freesia/Scene/Entity.h"
#include "Freesia/Scene/Components.h"

namespace Freesia
{
    Scene::~Scene()
    {
        m_Registry.view<NativeScriptComponent>().each([](auto entity, auto& ncs)
            {
                if (ncs.Instance)
                {
                    ncs.Instance->OnDestroy();
                    ncs.DestroyScript(&ncs);
                }
            });
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity(m_Registry.create(), this);
        entity.AddComponent<TransformComponent>();
        auto& tag = name.empty() ? "Entity" : name;
        entity.AddComponent<TagComponent>(tag);

        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

    void Scene::OnUpdate(TimeStep ts)
    {
        // Update scripts
        m_Registry.view<NativeScriptComponent>().each([&](auto entity, auto& ncs)
            {
                if (!ncs.Instance)
                {
                    ncs.Instance = ncs.InstantiateScript();
                    ncs.Instance->m_Entity = { entity, this };
                    ncs.Instance->OnCreate();
                }

                ncs.Instance->OnUpdate(ts);
            });

        Camera* mainCamera = nullptr;
        glm::mat4 cameraView = glm::mat4(1.0f);

        auto view = m_Registry.view<CameraComponent>();
        for (auto entity : view)
        {
            auto [cameraComp, transComp] = m_Registry.get<CameraComponent, TransformComponent>(entity);
            if (cameraComp.Camera.IsPrimary)
            {
                mainCamera = &cameraComp.Camera;
                cameraView = cameraComp.Camera.GetView() * transComp.GetTransform();
            }
        }

        if (mainCamera)
        {
            Renderer::BeginScene(*mainCamera, cameraView);
            {
                auto entityWithMesh = m_Registry.view<MeshComponent>();
                for (auto entity : entityWithMesh)
                {
                    auto meshComp = m_Registry.get<MeshComponent>(entity);
                    if (!m_Registry.any_of<TransformComponent>(entity)) continue;
                    auto transform = m_Registry.get<TransformComponent>(entity);
                    for (const auto& mesh : meshComp.Mesh.GetMeshes())
                    {
                        auto color = glm::vec4(1.0f);
                        if (m_Registry.any_of<SpriteRendererComponent>(entity))
                            color = m_Registry.get<SpriteRendererComponent>(entity).Color;
                        Renderer::DrawMesh(transform.GetTransform(), mesh, color);
                    }
                }
            }
            Renderer::EndScene();
        }
    }

    void Scene::OnViewportResize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width, m_ViewportHeight = height;

        auto view = m_Registry.view<CameraComponent>();

        for (auto entity : view)
        {
            auto& cameraComponent = m_Registry.get<CameraComponent>(entity);
            if (!cameraComponent.Camera.FixedAspectRatio)
                cameraComponent.Camera.SetViewportSize(width, height);
        }
    }

    template<typename T>
    void Scene::OnComponentAdded(Entity entity, T &component)
    {
        FS_CORE_ASSERT(false)
    }

    template<>
    void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
    {
        if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
            component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
    }

    template<>
    void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
    {}

    template<>
    void Scene::OnComponentAdded<MeshComponent>(Entity entity, MeshComponent& component)
    {}
}
