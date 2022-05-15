#pragma once

#include <string>

namespace Solar
{
    class Shader
    {
    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Bind();
        void UnBind();

    private:
        uint32_t mRendererID = -1;
    };
}