#pragma once

#include <vector>

#include "Solar/Core.h"

namespace Solar
{
    enum class ShaderDataType
    {
        None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::None:       SL_CORE_ERROR("Used none type"); return 0;
            case ShaderDataType::Float:      return 4;
            case ShaderDataType::Float2:     return 4 * 2;
            case ShaderDataType::Float3:     return 4 * 3;
            case ShaderDataType::Float4:     return 4 * 4;
            case ShaderDataType::Mat3:       return 4 * 3 * 4;
            case ShaderDataType::Mat4:       return 4 * 4 * 4;
            case ShaderDataType::Int:        return 4;
            case ShaderDataType::Int2:       return 4 * 2;
            case ShaderDataType::Int3:       return 4 * 3;
            case ShaderDataType::Int4:       return 4 * 4;
            case ShaderDataType::Bool:       return 1;
        }

        SL_CORE_ASSERT(false);
        return 0;
    }

    struct BufferElement
    {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            :Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {

        }

        uint32_t GetComponentCount() const
        {
            switch (Type)
            {
                case ShaderDataType::None:      SL_CORE_ERROR("Used none type"); return 0;;
                case ShaderDataType::Float:     return 1;
                case ShaderDataType::Float2:    return 2;
                case ShaderDataType::Float3:    return 3;
                case ShaderDataType::Float4:    return 4;
                case ShaderDataType::Mat3:      return 3 * 3;
                case ShaderDataType::Mat4:      return 4 * 4;
                case ShaderDataType::Int:       return 1;
                case ShaderDataType::Int2:      return 2;
                case ShaderDataType::Int3:      return 3;
                case ShaderDataType::Int4:      return 4;
                case ShaderDataType::Bool:      return 1;
            }   

            SL_CORE_ASSERT(false);
            return 0;
        }
    };

    class BufferLayout
    {
    public:
        BufferLayout(const std::initializer_list<BufferElement>& elements)
            : mElements(elements)
        {
            CalculateOffsetAndStride();
        }

        BufferLayout() {}

        uint32_t GetStrider() const { return mStride; }
        const std::vector<BufferElement>& GetElements() const { return mElements; }
    private:
        void CalculateOffsetAndStride()
        {
            uint32_t offset = 0;
            mStride = 0;
            for (auto& element : mElements)
            {
                element.Offset = offset;
                offset += element.Size;
                mStride += element.Size;
            }
        }
    private:
        std::vector<BufferElement> mElements;
        uint32_t mStride = 0;
    };

    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& layout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;

        static VertexBuffer* Create(float* vertices, uint32_t size);
    };

    class ElementBuffer
    {
    public:
        virtual ~ElementBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static ElementBuffer* Create(uint32_t* indices, uint32_t size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* indices, uint32_t size);
    };
}
