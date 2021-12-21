//
// Created by htrap19 on 12/18/21.
//

#ifndef FREESIA_ENTITY_H
#define FREESIA_ENTITY_H

#include "Freesia/Core/Assert.h"

#include "Freesia/Scene/Scene.h"

namespace Freesia
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity entity, Scene* scene);
        Entity(const Entity&) = default;

        template<typename T, typename ... Args>
        T& AddComponent(Args&& ... args)
        {
            FS_CORE_ASSERT(!this->template HasComponent<T>(), "Entity already has component!");
            return m_Scene->m_Registry.template emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent()
        {
            FS_CORE_ASSERT(this->template HasComponent<T>(), "Entity does not have component");
            return m_Scene->m_Registry.template get<T>(m_EntityHandle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.template any_of<T>(m_EntityHandle);
        }

        template<typename T>
        void RemoveComponent()
        {
            FS_CORE_ASSERT(this->template HasComponent<T>(), "Entity does not have component");
            m_Scene->m_Registry.template remove<T>(m_EntityHandle);
        }

        operator bool() const { return m_Scene->m_Registry.valid(m_EntityHandle); }
        operator entt::entity() const { return m_EntityHandle; }
        operator uint32_t() const { return (uint32_t)m_EntityHandle; }

        inline bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
        inline bool operator!=(const Entity& other) const { return !(*this == other); }

    private:
        Scene* m_Scene = nullptr;
        entt::entity m_EntityHandle = entt::null;
    };
}

#endif //FREESIA_ENTITY_H
