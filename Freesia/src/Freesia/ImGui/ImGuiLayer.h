//
// Created by Htrap19 on 12/12/21.
//

#ifndef FREESIA_IMGUILAYER_H
#define FREESIA_IMGUILAYER_H

#include "Freesia/Core/Layer.h"

namespace Freesia
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override = default;

        void OnAttach() override;
        void OnDetach() override;
        void OnEvent(Event& e) override;

        void Begin();
        void End();

        inline void SetBlockEvent(bool block) { m_BlockEvents = block; }

    private:
        void SetDarkThemeColors();

    private:
        bool m_BlockEvents = true;
    };
}

#endif //FREESIA_IMGUILAYER_H
