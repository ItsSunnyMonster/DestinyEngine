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

#pragma once

#include "Destiny/Layer/Layer.hpp"

namespace Destiny {

class LayerStack {
public:
  LayerStack();
  ~LayerStack();

  void pushLayer(Layer *layer);
  void pushOverlay(Layer *overlay);
  void popLayer(Layer *layer);
  void popOverlay(Layer *overlay);

  std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
  std::vector<Layer *>::iterator end() { return m_Layers.end(); }

private:
  std::vector<Layer *> m_Layers;
  uint8_t m_LayerInsertIndex = 0;
};

} // namespace Destiny
