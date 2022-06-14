#pragma once

#include "Solar/Renderer/Shader.h"

namespace Solar
{
    namespace ShaderUtils
    {
        uint32_t CompileShader(uint32_t type, const std::string& source);
        uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderData ParseShader(const std::string& filePath);
    }
}
