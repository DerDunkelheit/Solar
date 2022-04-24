#pragma once

#include "Solar/Core.h"

namespace Solar
{
    class SOLAR_API FileReader
    {
    public:
        static std::string ReadFile(const std::string& filePath);
    };
}
