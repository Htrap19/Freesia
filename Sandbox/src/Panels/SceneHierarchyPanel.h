//
// Created by htrap19 on 12/30/21.
//

#ifndef FREESIA_SCENEHIERARCHYPANEL_H
#define FREESIA_SCENEHIERARCHYPANEL_H

#include "Freesia/Core/Core.h"

#include "Freesia/Scene/Scene.h"
#include "Freesia/Scene/Entity.h"

namespace Freesia
{
    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;
        explicit SceneHierarchyPanel(const Ref<Scene>& context);

        void SetContext(const Ref<Scene>& context);

        void OnImGuiRender();

        inline Entity GetSelectedEntity() const { return m_SelectedContext; }

    private:
        void DrawEntityNode(Entity entity);
        void DrawComponents(Entity entity);

        template <typename T>
        void AddComponent(const std::string& componentStringified);

    private:
        Ref<Scene> m_Context;
        Entity m_SelectedContext;
    };
}

#endif //FREESIA_SCENEHIERARCHYPANEL_H
