//
// Created by htrap19 on 12/19/21.
//

#ifndef FREESIA_SCRIPTABLEENTITY_H
#define FREESIA_SCRIPTABLEENTITY_H

#include "Freesia/Scene/Entity.h"

namespace Freesia
{
    class ScriptableEntity
    {
    public:
        virtual ~ScriptableEntity() = default;

        template<typename T>
        T& GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(TimeStep ts) {}

    private:
        Entity m_Entity;
        friend class Scene;
    };
}

#endif //FREESIA_SCRIPTABLEENTITY_H
