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

#include "Destiny/Events/EventListener.hpp"

#include "Destiny/Renderer/GraphicsContext.hpp"

namespace Destiny {

struct WindowProps {
  std::string title;
  uint16_t width;
  uint16_t height;

  WindowProps(const std::string &title =
                  "Destiny Engine 使命游戏引擎 ciǎ seî hǔ jiù wâ nǘ ho̱ à",
              uint16_t width = 800, uint16_t height = 600)
      : title(title), width(width), height(height) {}
};

class Window {
public:
  virtual ~Window() {}
  virtual void onUpdate() = 0;

  virtual uint16_t getWidth() const = 0;
  virtual uint16_t getHeight() const = 0;

  virtual void setEventListener(EventListener &listener) = 0;

  virtual GraphicsContext *getContext() = 0;

  virtual void initImGuiImpl() = 0;
  virtual void imGuiNewFrame() = 0;
  virtual void destroyImGuiImpl() = 0;

  virtual void *getNativeWindow() = 0;

  static Window *create(const WindowProps &props = WindowProps());

protected:
  GraphicsContext *m_Context = nullptr;
};

} // namespace Destiny
