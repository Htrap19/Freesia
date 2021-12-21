//
// Created by htrap19 on 12/18/21.
//

#include "Scene.h"

#include "Freesia/Scene/Entity.h"
#include "Freesia/Scene/Components.h"

namespace Freesia
{
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
            auto cameraComp = m_Registry.get<CameraComponent>(entity);
            if (cameraComp.Camera.IsPrimary)
            {
                mainCamera = &cameraComp.Camera;
                cameraView = cameraComp.Camera.GetView();
            }
        }

        if (mainCamera)
        {
            Renderer::BeginScene(*mainCamera, cameraView);
            {
                auto entityWithMesh = m_Registry.view<MeshComponent>();
                for (auto entity : entityWithMesh)
                {
                    auto [meshComp, transform] = m_Registry.get<MeshComponent, TransformComponent>(entity);
                    for (const auto& mesh : meshComp.Mesh.GetMeshes())
                        Renderer::DrawMesh(transform.GetTransform(), mesh);
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
}
