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
#include "Destiny/KeyCodes.hpp"

namespace Destiny {

class KeyEvent : public Event {
public:
  KeyCode getKeyCode() const { return m_KeyCode; }

  EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
  KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}

  KeyCode m_KeyCode;
};

class KeyPressEvent : public KeyEvent {
public:
  KeyPressEvent(const KeyCode keycode, const uint16_t repeatCount)
      : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

  uint16_t getRepeatCount() const { return m_RepeatCount; }

  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyPressEvent: " << m_KeyCode << " (" << m_RepeatCount
       << " repeats)";
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyPress)
private:
  uint16_t m_RepeatCount;
};

class KeyReleaseEvent : public KeyEvent {
public:
  KeyReleaseEvent(const KeyCode keycode) : KeyEvent(keycode) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyReleaseEvent: " << m_KeyCode;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyRelease)
};

class KeyTypeEvent : public Event {
public:
  KeyTypeEvent(const char c) : m_Char(c) {}

  std::string toString() const override {
    std::stringstream ss;
    ss << "KeyTypeEvent: " << m_Char;
    return ss.str();
  }

  EVENT_CLASS_TYPE(KeyType)
  EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput |
                       EventCategory::EventCategoryKeyboard)

private:
  char m_Char;
};

} // namespace Destiny