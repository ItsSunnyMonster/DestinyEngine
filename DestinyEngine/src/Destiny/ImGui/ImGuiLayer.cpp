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
#include <backends/imgui_impl_win32.h>

Destiny::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

Destiny::ImGuiLayer::~ImGuiLayer() {}

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

  ImFontConfig config;
  config.Density = ImGui_ImplWin32_GetDpiScaleForHwnd(
      Application::get()->getWindow()->getNativeWindow());
  config.OversampleH = 1;
  config.OversampleV = 1;
  config.FontBuilderFlags = 1;
  io.Fonts->AddFontFromFileTTF(
      "assets/fonts/cjk/NotoSansSC-Regular.otf", 20, &config,
      io.Fonts->GetGlyphRangesChineseSimplifiedCommon());

  Ref<Window> wnd = Application::get()->getWindow();
  wnd->initImGuiImpl();
  wnd->getContext()->initImGuiImpl();
}

void Destiny::ImGuiLayer::onDetach() {
  Ref<Window> wnd = Application::get()->getWindow();
  wnd->destroyImGuiImpl();
  wnd->getContext()->destroyImGuiImpl();
  ImGui::DestroyContext();
}

void Destiny::ImGuiLayer::onUpdate() {}

void Destiny::ImGuiLayer::onEvent(Event &event) {}

void Destiny::ImGuiLayer::onImGuiRender() {
  static bool show;
  ImGui::ShowDemoWindow(&show);
}
