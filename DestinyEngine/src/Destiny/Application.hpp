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

#include "Window.hpp"
#include "Destiny/Events/EventListener.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/Layer/LayerStack.hpp"

namespace Destiny {

class Application : public EventListener {
public:
  Application();
  virtual ~Application();
  void run();
  void onEvent(Event &event) override;
  void pushLayer(Layer *layer) { m_LayerStack.pushLayer(layer); }
  void pushOverlay(Layer *layer) { m_LayerStack.pushOverlay(layer); }

  inline Ref<Window> getWindow() { return m_Window; }

  inline static Application *get() { return s_Instance; }

private:
  bool m_Running;
  Ref<Window> m_Window;
  Layer *m_ImGuiLayer;
  LayerStack m_LayerStack;

  static Application *s_Instance;

private:
  bool onWindowCloseEvent(WindowCloseEvent &e);
};

// To be defined in CLIENT
Application *createApplication();

} // namespace Destiny