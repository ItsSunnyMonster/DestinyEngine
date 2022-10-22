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

#include <dtpch.hpp>

namespace Destiny {

class GraphicsContext {
public:
  virtual ~GraphicsContext() = default;

  virtual void swap() = 0;

  virtual bool isVSync() = 0;
  virtual void setVSync(bool enabled) = 0;
  virtual void resize(unsigned int width, unsigned int height) = 0;

  virtual void initImGuiImpl() = 0;
  virtual void imGuiNewFrame() = 0;
  virtual void destroyImGuiImpl() = 0;
  virtual void imGuiRender() = 0;
  virtual void imGuiReCreateFontsTexture() = 0;

  virtual void clear() = 0;

protected:
  GraphicsContext(bool vSync, uint16_t width, uint16_t height)
      : m_VSync(vSync), m_Width(width), m_Height(height) {}

  bool m_VSync;
  uint16_t m_Width;
  uint16_t m_Height;
};

} // namespace Destiny
