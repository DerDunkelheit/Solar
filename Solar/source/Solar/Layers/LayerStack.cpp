#include "slpch.h"

#include "LayerStack.h"
#include "Layer.h"

namespace Solar
{
    LayerStack::LayerStack()
    {
       
    }

    LayerStack::~LayerStack()
    {
        for(const Layer* layer : mLayers)
        {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        //We use mLayerInsert in order to place layer, so overlays are always in front of layers.
        mLayers.emplace(mLayers.begin()+ mLayerInsertIndex, layer);
        mLayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        mLayers.emplace_back(overlay);
    }

    void LayerStack::PopLayer(const Layer* layer)
    {
        const auto it = std::find(mLayers.begin(), mLayers.end(), layer);
        if (it != mLayers.end())
        {
            mLayers.erase(it);
            mLayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        const auto it = std::find(mLayers.begin(), mLayers.end(), overlay);
        if (it != mLayers.end())
        {
            mLayers.erase(it);
        }
    }
}
