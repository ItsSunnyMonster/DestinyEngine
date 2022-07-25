/*
 *   Copyright (c) 2022 ItsSunnyMonster

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "LayerStack.hpp"

Destiny::LayerStack::LayerStack() {}

Destiny::LayerStack::~LayerStack() {
  for (Layer *layer : m_Layers) {
    layer->onDetach();
    delete layer;
  }
}

void Destiny::LayerStack::pushLayer(Layer *layer) {
  m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
  m_LayerInsertIndex++;
  layer->onAttach();
}

void Destiny::LayerStack::pushOverlay(Layer *overlay) {
  m_Layers.emplace_back(overlay);
  overlay->onAttach();
}

void Destiny::LayerStack::popLayer(Layer *layer) {
  auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
  // If it == m_Layers.end() that means the layer was not found
  if (it != m_Layers.end()) {
    // Remove the iterator (element) from the vector
    m_Layers.erase(it);
    m_LayerInsertIndex--;
    layer->onDetach();
  }
}

void Destiny::LayerStack::popOverlay(Layer *overlay) {
  auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
  if (it != m_Layers.end()) {
    // Remove the element from the vector without decrementing the interator
    m_Layers.erase(it);
    overlay->onDetach();
  }
}
