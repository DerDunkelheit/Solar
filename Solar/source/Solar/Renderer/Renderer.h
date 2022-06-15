#pragma once

#include "RendererAPI.h"

namespace Solar
{
    class Renderer
    {
    public:
        static RendererAPI::API GetCurrentAPI() { return RendererAPI::GetAPI(); }

        static void BeginScene();
        static void EndScene();
        
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static void SubmitElementBuffer(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount);
    };
}
