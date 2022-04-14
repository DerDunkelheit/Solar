#include "slpch.h"

#include "LayerStack.h"
#include "Layer.h"

namespace Solar
{
    LayerStack::LayerStack()
    {
        mLayerInsert = mLayers.begin();
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
        mLayerInsert = mLayers.emplace(mLayerInsert, layer);
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
            --mLayerInsert;
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
