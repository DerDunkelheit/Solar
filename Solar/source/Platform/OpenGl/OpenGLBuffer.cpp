#include "slpch.h"

#include <glad/glad.h>

#include "OpenGLBuffer.h"

namespace Solar
{
    /////////////////////////////////////////////////////////////////////////
    // VertexBuffer //////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        glGenBuffers(1, &mRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////
    // ElementBuffer //////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////

    OpenGLElementBuffer::OpenGLElementBuffer(uint32_t* indices, uint32_t size)
    {
        glGenBuffers(1, &mRendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    OpenGLElementBuffer::~OpenGLElementBuffer()
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLElementBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLElementBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    /////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
        :mCount(count)
    {
        glCreateBuffers(1, &mRendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &mRendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}