#include "pch.h"
#include "LayerStack.h"


namespace Blimp {
    LayerStack::LayerStack() {
        m_LayerInsert = 0;
    }
    
    LayerStack::~LayerStack(){
        for(Layer* layer : m_Layers) {
            layer->OnDetach();
            delete layer;
            layer = nullptr;
        }
    }

    void LayerStack::PushLayer(Layer *layer) {
        m_Layers.emplace(m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsert), layer);
        ++m_LayerInsert;
    }

    void LayerStack::PopLayer(Layer *layer) {
        auto end = m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsert);
        auto it = std::find(m_Layers.begin(), end, layer);
        if (it != end) {
            (*it)->OnDetach();
            delete *it;
            m_Layers.erase(it);
            --m_LayerInsert;
        }
    }
    
    void LayerStack::PushOverlay(Layer *overlay) {
        m_Layers.emplace_back(overlay);
    }

    void LayerStack::PopOverlay(Layer *overlay) {
        auto begin = m_Layers.begin() + static_cast<std::ptrdiff_t>(m_LayerInsert);
        auto it = std::find(begin, m_Layers.end(), overlay);
        if (it != m_Layers.end()) {
            (*it)->OnDetach();
            delete *it;
            m_Layers.erase(it);
        }
    }
} // namespace Blimp
