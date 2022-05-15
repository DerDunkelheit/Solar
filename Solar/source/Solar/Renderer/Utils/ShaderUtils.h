#pragma once

#include <string>

namespace Solar
{
    namespace ShaderUtils
    {
        struct ShaderData
        {
            std::string VertexShader;
            std::string FragmentShader;
        };

        uint32_t CompileShader(uint32_t type, const std::string& source);
        uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        ShaderData ParseShader(const std::string& filePath);
    }
}