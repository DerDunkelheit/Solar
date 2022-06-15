#include "slpch.h"

#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGl/OpenGLVertexArray.h"

namespace Solar
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPI::API::None:   SL_CORE_ASSERT(false);
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }

        SL_CORE_ASSERT(false);
        return nullptr;
    }
}
