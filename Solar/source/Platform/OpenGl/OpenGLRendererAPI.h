#pragma once

#include "Solar/Renderer/RendererAPI.h"

namespace Solar
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void SetClearColor(const glm::vec4& color) override;
        void Clear() override;
        void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
        void DrawElementBuffered(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount) override;
        
        void UpdateViewportSize(uint32_t width, uint32_t height) override;
    };
}
