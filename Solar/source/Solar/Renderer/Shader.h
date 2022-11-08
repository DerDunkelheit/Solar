#pragma once

#include <glm/vec4.hpp>

namespace Solar
{
    struct ShaderData
    {
        std::string VertexShader;
        std::string FragmentShader;
    };
    
    //TODO: make an abstract class and create an OpenGLShader?
    class Shader
    {
    public:
        Shader(ShaderData data);

        void Bind() const;
        void UnBind() const;
        void setFloat(const std::string& name, float value) const;
        void SetInt(const std::string& name, int value) const;
        void SetColor(const std::string& name, glm::vec4 color) const;

        int GetLocation(const char* variableName) const;

        uint32_t GetRendererId() const { return mRendererId; }

    private:
        uint32_t mRendererId;
        ShaderData mShaderData;
    };
}
