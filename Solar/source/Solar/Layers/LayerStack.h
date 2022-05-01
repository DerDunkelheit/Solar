#pragma once

#include "Solar/Core.h"

namespace Solar
{
    class Layer;

    class SOLAR_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopLayer(const Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
        std::vector<Layer*>::iterator end() { return mLayers.end(); }
        
    private:
        std::vector<Layer*> mLayers;
        uint32_t mLayerInsertIndex = 0;
    };
}
