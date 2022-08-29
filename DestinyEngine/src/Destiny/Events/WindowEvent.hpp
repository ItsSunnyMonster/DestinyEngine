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

// Credit to the Hazel Engine by TheCherno on Github
// https://github.com/TheCherno/Hazel

#pragma once

#include "Destiny/Events/Event.hpp"

namespace Destiny {

class WindowResizeEvent : public Event {
public:
  WindowResizeEvent(uint16_t width, uint16_t height)
      : m_Width(width), m_Height(height) {}

  uint16_t getWidth() const { return m_Width; }
  uint16_t getHeight() const { return m_Height; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowResize)
  EVENT_CLASS_CATEGORY(EventCategoryWindow)
private:
  uint16_t m_Width, m_Height;
};

class WindowCloseEvent : public Event {
public:
  WindowCloseEvent() = default;

  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowCloseEvent";
    return ss.str();
  }

  EVENT_CLASS_TYPE(WindowClose)
  EVENT_CLASS_CATEGORY(EventCategoryWindow)
};

class WindowDPIChangeEvent : public Event {
public:
  WindowDPIChangeEvent(float dpi) : m_DPI(dpi) {}
  float getDPI() const { return m_DPI; }
  std::string toString() const override {
    std::stringstream ss;
    ss << "WindowDPIChangeEvent: " << m_DPI;
    return ss.str();
  }
  EVENT_CLASS_TYPE(WindowDPIChange)
  EVENT_CLASS_CATEGORY(EventCategoryWindow)
private:
  float m_DPI;
};

} // namespace Destiny