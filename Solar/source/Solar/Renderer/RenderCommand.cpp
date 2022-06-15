#include "slpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace Solar
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}
