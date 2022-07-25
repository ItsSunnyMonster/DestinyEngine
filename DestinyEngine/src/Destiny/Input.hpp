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

#include "Destiny/KeyCodes.hpp"
#include "Destiny/MouseCodes.hpp"

namespace Destiny {
class Input {
public:
  inline static bool isKeyPressed(KeyCode keyCode) {
    return s_Instance->_isKeyPressed(keyCode);
  }
  inline static bool isMouseButtonPressed(MouseCode button) {
    return s_Instance->_isMouseButtonPressed(button);
  }
  inline static std::pair<float, float> getMousePosition() {
    return s_Instance->_getMousePosition();
  }
  inline static float getMouseX() { return getMousePosition().first; }
  inline static float getMouseY() { return getMousePosition().second; }

protected:
  virtual bool _isKeyPressed(KeyCode keyCode) = 0;
  virtual bool _isMouseButtonPressed(MouseCode button) = 0;
  virtual std::pair<float, float> _getMousePosition() = 0;

private:
  static Input *s_Instance;
};
} // namespace Destiny
