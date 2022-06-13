#include "slpch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGLBuffer.h"

namespace Solar
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Renderer::GetCurrentAPI())
        {
        case RendererAPI::None:
            break;

        case RendererAPI::OpenGL:
            return new OpenGLVertexBuffer(vertices, size);
            break;
        }

        return nullptr;
    }

    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetCurrentAPI())
        {
        case RendererAPI::None:
            break;

        case RendererAPI::OpenGL:
            return new OpenGLIndexBuffer(indices, size);
            break;
        }

        return nullptr;
    }

    ElementBuffer* ElementBuffer::Create(uint32_t* indices, uint32_t size)
    {
        switch (Renderer::GetCurrentAPI())
        {
        case RendererAPI::None:
            break;

        case RendererAPI::OpenGL:
            return new OpenGLElementBuffer(indices, size);
            break;
        }

        return nullptr;
    }
}