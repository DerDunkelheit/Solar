#pragma once

#include "Solar/Core.h"

namespace Solar
{
    class SOLAR_API Input
    {
    public:
        static bool IsKeyPressed(int keycode);
        static bool IsMouseButtonPressed(int button);
        static float GetMouseX();
        static float GetMouseY();
    };
}
