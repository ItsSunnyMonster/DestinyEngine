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

#include "ImGuiLayer.hpp"

#include <imgui.h>

#include "Destiny/Application.hpp"

Destiny::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"), m_DPIChanged(false) {}

Destiny::ImGuiLayer::~ImGuiLayer() = default;

void Destiny::ImGuiLayer::onAttach() {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();

  ImGuiIO &io = ImGui::GetIO();
  // io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
  // io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  Ref<Window> wnd = Application::get()->getWindow();

  ImFontConfig config;
  config.OversampleH = 1;
  config.OversampleV = 1;
  config.FontBuilderFlags = 1;
  io.Fonts->AddFontFromFileTTF(
      "assets/fonts/cjk/NotoSansSC-Regular.otf", 20 * wnd->getDPIScale(),
      &config, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
  // ImGui::GetStyle().ScaleAllSizes(wnd->getDPIScale());

  wnd->initImGuiImpl();
  wnd->getContext()->initImGuiImpl();
}

void Destiny::ImGuiLayer::onDetach() {
  Ref<Window> wnd = Application::get()->getWindow();
  wnd->destroyImGuiImpl();
  wnd->getContext()->destroyImGuiImpl();
  ImGui::DestroyContext();
}

void Destiny::ImGuiLayer::onUpdate() {
  if (m_DPIChanged) {
    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF(
        "assets/fonts/cjk/NotoSansSC-Regular.otf", 20 * m_DPI, nullptr,
        io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    // io.Fonts->GetTexDataAsRGBA32(nullptr, nullptr, nullptr);
    io.Fonts->Build();
    Application::get()->getWindow()->getContext()->imGuiReCreateFontsTexture();
    m_DPIChanged = false;
  }
}

void Destiny::ImGuiLayer::onEvent(Event &event) {
  EventDispatcher dispatcher = EventDispatcher(event);
  dispatcher.dispatch<WindowDPIChangeEvent>(
      BIND_EVENT_FN(ImGuiLayer::onDPIChanged));
}

bool Destiny::ImGuiLayer::onDPIChanged(WindowDPIChangeEvent &event) {
  m_DPIChanged = true;
  m_DPI = event.getDPI();
  return true;
}

void Destiny::ImGuiLayer::onImGuiRender() {
  static bool show;
  ImGui::ShowDemoWindow(&show);
}
