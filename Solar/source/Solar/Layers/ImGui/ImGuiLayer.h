#pragma once

#include "Solar/Layers/Layer.h"

namespace Solar
{
    class SOLAR_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& event) override;

    private:
        float mTime = 0;
    };
}
