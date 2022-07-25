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

#include "Destiny/Macros.hpp"
#include <spdlog/fmt/ostr.h>

namespace Destiny {

enum class EventType {
  None = 0,
  WindowClose,
  WindowResize,
  WindowMove,
  WindowFocus,
  WindowUnfocus,
  KeyPress,
  KeyRelease,
  KeyType,
  MouseButtonPress,
  MouseButtonRelease,
  MouseMove,
  MouseScroll
};

enum EventCategory {
  None = 0,
  EventCategoryWindow = BIT(0),
  EventCategoryInput = BIT(1),
  EventCategoryKeyboard = BIT(2),
  EventCategoryMouse = BIT(3),
  EventCategoryMouseButton = BIT(4),
};

#define EVENT_CLASS_TYPE(type)                                                 \
  static EventType getStaticType() { return EventType::type; }                 \
  virtual EventType getEventType() const override { return getStaticType(); }  \
  virtual const char *getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)                                         \
  virtual uint8_t getCategoryFlags() const override { return category; }

class Event {
public:
  virtual ~Event() = default;

  bool handled = false;

  virtual EventType getEventType() const = 0;
  virtual const char *getName() const = 0;
  virtual uint8_t getCategoryFlags() const = 0;
  virtual std::string toString() const { return getName(); }

  bool isInCategory(EventCategory category) {
    return getCategoryFlags() & category;
  }

  template <typename OStream>
  friend OStream &operator<<(OStream &os, const Event &e) {
    return os << e.toString();
  }
};

class EventDispatcher {
public:
  EventDispatcher(Event &event) : m_Event(event) {}

  // F will be deduced by the compiler
  template <typename T, typename F> bool dispatch(const F &func) {
    if (m_Event.getEventType() == T::getStaticType()) {
      m_Event.handled |= func(static_cast<T &>(m_Event));
      return true;
    }
    return false;
  }

private:
  Event &m_Event;
};

} // namespace Destiny