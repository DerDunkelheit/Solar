#include "slpch.h"

#include "Renderer.h"
#include "RenderCommand.h"

namespace Solar
{
    void Renderer::BeginScene()
    {
        
    }

    void Renderer::EndScene()
    {
        
    }

    void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::SubmitElementBuffer(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount)
    {
        vertexArray->Bind();
        RenderCommand::DrawElementBuffered(vertexArray, verticesCount);
    }
}
