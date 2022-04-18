#include "LayerStack.hpp" 

Destiny::LayerStack::LayerStack()
{
	// m_Layers.begin() will return the iterator of the end of the vector
	// since m_Layers will initially be empty
	m_LayerInsert = m_Layers.begin();
}

Destiny::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers)
	{
		delete layer;
	}
}

void Destiny::LayerStack::pushLayer(Layer* layer)
{
	// The new layer will be emplaced to the back of m_LayerInsert
	// m_LayerInsert can be seen as a bookmark in the middle of the vector
	// When the layer gets emplaced to the back of m_LayerInsert
	// the m_LayerInsert iterator also gets moved to the back of the newly inserted element
	m_Layers.emplace(m_LayerInsert, layer);
}

void Destiny::LayerStack::pushOverlay(Layer* overlay)
{
	// emplace_back() is exactly the same as push_back()
	// When the overlay gets pushed in, 
	// it does NOT increment the m_LayerInsert iterator
	// Therefore new layers will still be pushed to places UNDER the overlays
	m_Layers.emplace_back(overlay);
}

void Destiny::LayerStack::popLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	// If it == m_Layers.end() that means the layer was not found
	if (it != m_Layers.end())
	{
		// Remove the iterator (element) from the vector
		m_Layers.erase(it);
		// Decrement the m_LayerInsert iterator to match the change
		m_LayerInsert--;
	}
}

void Destiny::LayerStack::popOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	if (it != m_Layers.end())
		// Remove the element from the vector without decrementing the interator
		m_Layers.erase(it);
}
