#include "LayerStack.hpp" 

Destiny::LayerStack::LayerStack()
{
}

Destiny::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		layer->onDetach();
		delete layer;
	}
}

void Destiny::LayerStack::pushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
	m_LayerInsertIndex++;
	layer->onAttach();
}

void Destiny::LayerStack::pushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->onAttach();
}

void Destiny::LayerStack::popLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	// If it == m_Layers.end() that means the layer was not found
	if (it != m_Layers.end())
	{
		// Remove the iterator (element) from the vector
		m_Layers.erase(it);
		m_LayerInsertIndex--;
		layer->onDetach();
	}
}

void Destiny::LayerStack::popOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end()) {
		// Remove the element from the vector without decrementing the interator
		m_Layers.erase(it);
		overlay->onDetach();
	}
}
