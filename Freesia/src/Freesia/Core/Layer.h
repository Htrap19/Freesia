//
// Created by Htrap19 on 12/4/21.
//

#ifndef FREESIA_LAYER_H
#define FREESIA_LAYER_H

#include <string>
#include <utility>

#include "Freesia/Core/Timestep.h"
#include "Freesia/Events/Event.h"

namespace Freesia
{
    class Layer
    {
    public:
        explicit Layer(std::string name = "Layer")
            : m_LayerName(std::move(name))
        {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OmUpdate(TimeStep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& e) {}

    private:
        std::string m_LayerName;
    };
}

#endif //FREESIA_LAYER_H
