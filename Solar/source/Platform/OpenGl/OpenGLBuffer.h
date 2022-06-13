#pragma once

#include "Solar/Renderer/Buffer.h"

namespace Solar
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetLayout(const BufferLayout& layout) override { mLayout = layout; };
        virtual const BufferLayout& GetLayout() const override { return mLayout; }
    private:
        uint32_t mRendererID;
        BufferLayout mLayout;
    };

    class OpenGLElementBuffer : public ElementBuffer
    {
    public:
        OpenGLElementBuffer(uint32_t* indices, uint32_t size);
        virtual ~OpenGLElementBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t mRendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual uint32_t GetCount() const override { return mCount; }

    private:
        uint32_t mRendererID;
        uint32_t mCount;
    };
}