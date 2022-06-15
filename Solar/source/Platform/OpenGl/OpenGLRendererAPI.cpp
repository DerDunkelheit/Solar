#include "slpch.h"

#include <glad/glad.h>

#include "OpenGLRendererAPI.h"

namespace Solar
{
    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawElementBuffered(const std::shared_ptr<VertexArray>& vertexArray, uint32_t verticesCount)
    {
        glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::UpdateViewportSize(uint32_t width, uint32_t height)
    {
        glViewport(0, 0, width, height);
    }
}
