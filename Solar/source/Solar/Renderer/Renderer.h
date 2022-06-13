#pragma once

namespace Solar
{
    enum class RendererAPI
    {
        //TODO: add directx 12 and vulkan support.
        None = 0,
        OpenGL = 1
    };

    class Renderer
    {
    public:
        static RendererAPI GetCurrentAPI() { return sRendererAPI; }
        static RendererAPI sRendererAPI;
    };
}