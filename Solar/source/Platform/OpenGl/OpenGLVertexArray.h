#pragma once
#include "Solar/Renderer/VertexArray.h"

namespace Solar
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        
        void Bind() const override;
        void UnBind() const override;
        
        void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        
        const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return mVertexBuffers; }
        const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return mIndexBuffer; }

    private:
        uint32_t mRendererID;
        std::vector<std::shared_ptr<VertexBuffer>> mVertexBuffers;
        std::shared_ptr<IndexBuffer> mIndexBuffer;
    };
}
