#include "slpch.h"

#include <glad/glad.h>

#include "OpenGLVertexArray.h"

namespace Solar
{
    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Int:       return GL_INT;
            case ShaderDataType::Int2:      return GL_INT;
            case ShaderDataType::Int3:      return GL_INT;
            case ShaderDataType::Int4:      return GL_INT;
            case ShaderDataType::Bool:      return GL_BYTE;
        }

        SL_CORE_ASSERT(false);
        return 0;
    }   
    
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &mRendererID);
        glBindVertexArray(mRendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &mRendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(mRendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        SL_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size());
        
        glBindVertexArray(mRendererID);
        vertexBuffer->Bind();

        uint32_t index = 0;
        const BufferLayout& layout = vertexBuffer->GetLayout();
        for (auto& element : layout.GetElements())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStrider(), reinterpret_cast<void*>(element.Offset));
            index++;
        }

        mVertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(mRendererID);
        indexBuffer->Bind();

        mIndexBuffer = indexBuffer;
    }
}
