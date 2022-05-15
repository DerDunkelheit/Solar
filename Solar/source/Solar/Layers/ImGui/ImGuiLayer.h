#pragma once

#include "Solar/Layers/Layer.h"

namespace Solar
{
    class SOLAR_API ImGuiLayer : public Layer
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;
        virtual void OnEvent(Event& event) override;

        void Begin();
        void End();

        //TODO: maybe replace to base class
        void SetEventCallback(const EventCallbackFn& callback) { mEventCallback = callback; }
    private:
        float mTime = 0;

        EventCallbackFn mEventCallback;
    };
}
