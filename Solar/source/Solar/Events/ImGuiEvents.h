#pragma once

#include "Solar/Events/Event.h"

namespace Solar
{
    class SOLAR_API ColorChangedEvent : public Event
    {
    public:
        ColorChangedEvent(float red, float green, float blue)
            : mRed(red), mGreen(green), mBlue(blue) {}

        float GetRedValue() const { return mRed; }
        float GetGreenValue() const { return mGreen; }
        float GetBlueValue() const { return mBlue; }

        EVENT_CLASS_TYPE(ColorChanged)
        EVENT_CLASS_CATEGORY(EventCaregoryImGui)

    private:
        float mRed;
        float mGreen;
        float mBlue;
    };
}