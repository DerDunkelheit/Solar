#pragma once

#include <glm/vec4.hpp>

#include "VertexArray.h"

namespace Solar
{
    class RendererAPI
    {
    public:
        virtual ~RendererAPI() = default;

        enum class API
        {
            //TODO: add directx 12 and vulkan support.
            None = 0,
            OpenGL = 1
        };
    public:
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
        virtual void DrawElementBuffered(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount) = 0;

        virtual void UpdateViewportSize(uint32_t width, uint32_t height) = 0;

        static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}

