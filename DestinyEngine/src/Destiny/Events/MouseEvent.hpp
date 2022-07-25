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
#include "Destiny/MouseCodes.hpp"

namespace Destiny {

class MouseMoveEvent : public Event {
public:
  MouseMoveEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

  float getX() const { return m_MouseX; }
  float getY() const { return m_MouseY; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseMove)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
  float m_MouseX, m_MouseY;
};

class MouseScrollEvent : public Event {
public:
  MouseScrollEvent(const float xOffset, const float yOffset)
      : m_XOffset(xOffset), m_YOffset(yOffset) {}

  float getXOffset() const { return m_XOffset; }
  float getYOffset() const { return m_YOffset; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseScrollEvent: " << getXOffset() << ", " << getYOffset();
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseScroll)
  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
  float m_XOffset, m_YOffset;
};

class MouseButtonEvent : public Event {
public:
  MouseCode getMouseButton() const { return m_Button; }

  EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput |
                       EventCategoryMouseButton)
protected:
  MouseButtonEvent(const MouseCode button) : m_Button(button) {}

  MouseCode m_Button;
};

class MouseButtonPressEvent : public MouseButtonEvent {
public:
  MouseButtonPressEvent(const MouseCode button) : MouseButtonEvent(button) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseButtonPressEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonPress)
};

class MouseButtonReleaseEvent : public MouseButtonEvent {
public:
  MouseButtonReleaseEvent(const MouseCode button) : MouseButtonEvent(button) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "MouseButtonReleaseEvent: " << m_Button;
    return ss.str();
  }

  EVENT_CLASS_TYPE(MouseButtonRelease)
};

} // namespace Destiny