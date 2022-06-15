#pragma once

#include "RendererAPI.h"

namespace Solar
{
    class RenderCommand
    {
    public:
        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }
        
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }

        static void DrawElementBuffered(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount)
        {
            s_RendererAPI->DrawElementBuffered(vertexArray, verticesCount);
        }

        static void UpdateViewportSize(uint32_t width, uint32_t height)
        {
            s_RendererAPI->UpdateViewportSize(width, height);
        }
        
    private:
        static RendererAPI* s_RendererAPI;
    };
}
