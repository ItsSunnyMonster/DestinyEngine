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

#include "Application.hpp"
#include "Destiny/Events/KeyboardEvent.hpp"
#include "Destiny/Events/MouseEvent.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/ImGui/ImGuiLayer.hpp"
#include "Log.hpp"
#include "Macros.hpp"

#include <Destiny/Platform/D3D11/D3D11Context.hpp>
#include <imgui.h>

namespace Destiny {

Application *Application::s_Instance;

Application::Application() : m_Running(true) {
  DT_ASSERT_MSG(!s_Instance, "s_Instance is not null!");
  s_Instance = this;

  m_Window = Ref<Window>(Window::create());
  m_Window->setEventListener(*this);

  m_ImGuiLayer = new ImGuiLayer();
  pushLayer(m_ImGuiLayer);
}

Application::~Application() = default;

void Application::run() {
  while (m_Running) {
    auto context = m_Window->getContext();

    // Update layers
    for (Layer *layer : m_LayerStack) {
      layer->onUpdate();
    }

    context->clear();

    // Start ImGui Frame
    context->imGuiNewFrame();
    m_Window->imGuiNewFrame();
    ImGui::NewFrame();
    // Render each layer
    for (Layer *layer : m_LayerStack) {
      layer->onImGuiRender();
    }

    // End ImGui Frame
    ImGui::Render();
    context->imGuiRender();
    // Update and Render additional Platform Windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
    }

    context->swap();

    m_Window->onUpdate();
  }
}
void Application::onEvent(Event &event) {
  EventDispatcher dispatcher = EventDispatcher(event);
  dispatcher.dispatch<WindowCloseEvent>(
      BIND_EVENT_FN(Application::onWindowCloseEvent));

  DT_CORE_TRACE("{0}", event);

  for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
    // (*--it) Decrements the iterator and dereferences it
    if ((*--it)->isEnabled()) {
      (*it)->onEvent(event);
      // If the event is handled then don't propogate anymore
      if (event.handled)
        break;
    }
  }
}

bool Application::onWindowCloseEvent(WindowCloseEvent &e) {
  m_Running = false;
  return true;
}
} // namespace Destiny
