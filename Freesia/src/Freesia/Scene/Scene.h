//
// Created by htrap19 on 12/18/21.
//

#ifndef FREESIA_SCENE_H
#define FREESIA_SCENE_H

#include <entt.hpp>

#include "Freesia/Core/Timestep.h"

#include "Freesia/Renderer/EditorCamera.h"

namespace Freesia
{
    class Entity;
    class Scene
    {
    public:
        Scene() = default;
        virtual ~Scene();

        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(Entity entity);

        void OnUpdateRuntime(TimeStep ts);
        void OnUpdateEditor(const EditorCamera& camera, TimeStep ts);
        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();

    private:
        template<typename T>
        void OnComponentAdded(Entity entity, T& component);

    private:
        entt::registry m_Registry;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;
        friend class SceneSerializer;
        friend class SceneHierarchyPanel;
    };
}

#endif //FREESIA_SCENE_H
