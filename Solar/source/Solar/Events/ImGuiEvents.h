#pragma once

#include <optional>

#include "Solar/Events/Event.h"

namespace Solar
{
    class SOLAR_API ColorChangedEvent : public Event
    {
    public:
        ColorChangedEvent(glm::vec4 color)
            : mColor(color) {}

        ColorChangedEvent(glm::vec4 color, const std::string& propertyName)
            : mColor(color), mPropertyName(propertyName) {}

        glm::vec4 GetColor() const { return mColor; }
        const std::optional<std::string>& GetPropertyName() const { return mPropertyName; }

        EVENT_CLASS_TYPE(ColorChanged)
        EVENT_CLASS_CATEGORY(EventCaregoryImGui)

    private:
        glm::vec4 mColor;
        
        std::optional<std::string> mPropertyName;
    };
}