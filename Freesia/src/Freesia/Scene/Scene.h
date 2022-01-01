//
// Created by htrap19 on 12/18/21.
//

#ifndef FREESIA_SCENE_H
#define FREESIA_SCENE_H

#include <entt.hpp>

#include "Freesia/Core/Timestep.h"

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

        void OnUpdate(TimeStep ts);
        void OnViewportResize(uint32_t width, uint32_t height);

    private:
        entt::registry m_Registry;
        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };
}

#endif //FREESIA_SCENE_H
