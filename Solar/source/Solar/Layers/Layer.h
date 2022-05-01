#pragma once

#include "Solar/Core.h"
#include "Solar/Events/Event.h"

namespace Solar
{
    class SOLAR_API Layer
    {
    public:
        Layer(const std::string& debugName = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event& event) {}

        const std::string& GetName() const
        {
            return mDebugName;
        }

    protected:
        std::string mDebugName;
    };
}