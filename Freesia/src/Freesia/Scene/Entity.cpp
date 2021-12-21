//
// Created by htrap19 on 12/18/21.
//

#include "Entity.h"

namespace Freesia
{
    Entity::Entity(entt::entity entity, Scene *scene)
        : m_EntityHandle(entity), m_Scene(scene)
    {
    }
}