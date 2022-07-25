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

#include "WindowsInput.hpp"

#include "WindowsWindow.hpp"

#include "Destiny/Application.hpp"

bool Destiny::WindowsInput::s_MouseCodeInitialized = false;

bool Destiny::WindowsInput::s_KeyMapInitialized = false;

std::unordered_map<Destiny::Win32KeyCode, Destiny::KeyCode>
    Destiny::WindowsInput::s_KeyMapWin32ToDT;
std::unordered_map<Destiny::KeyCode, Destiny::Win32KeyCode>
    Destiny::WindowsInput::s_KeyMapDTToWin32;
std::unordered_map<Destiny::Win32MouseCode, Destiny::MouseCode>
    Destiny::WindowsInput::s_MouseMapWin32ToDT;
std::unordered_map<Destiny::MouseCode, Destiny::Win32MouseCode>
    Destiny::WindowsInput::s_MouseMapDTToWin32;

Destiny::Input *Destiny::Input::s_Instance = new WindowsInput();

Destiny::WindowsInput::WindowsInput() {
  if (!s_KeyMapInitialized) {
    initializeKeyMap();
  }
  if (!s_MouseCodeInitialized) {
    initializeMouseMap();
  }
}

bool Destiny::WindowsInput::_isKeyPressed(KeyCode keyCode) {
  if (GetForegroundWindow() !=
      Application::get()->getWindow()->getNativeWindow()) {
    return false;
  }
  SHORT keyState = GetAsyncKeyState(keyMapDTToWin32(keyCode));
  return (1 << 15) & keyState;
}

bool Destiny::WindowsInput::_isMouseButtonPressed(MouseCode button) {
  if (GetForegroundWindow() !=
      Application::get()->getWindow()->getNativeWindow()) {
    return false;
  }
  return GetAsyncKeyState(mouseMapDTToWin32(button));
}

std::pair<float, float> Destiny::WindowsInput::_getMousePosition() {
  POINT mousePos;
  GetCursorPos(&mousePos);
  ScreenToClient((HWND)Application::get()->getWindow()->getNativeWindow(),
                 &mousePos);
  return std::pair<float, float>(static_cast<float>(mousePos.x),
                                 static_cast<float>(mousePos.y));
}

#define REGISTER_KEY(key) s_KeyMapDTToWin32[key] = Win32::key

void Destiny::WindowsInput::initializeKeyMap() {
  REGISTER_KEY(Key::Space);
  REGISTER_KEY(Key::Apostrophe);
  REGISTER_KEY(Key::Comma);
  REGISTER_KEY(Key::Minus);
  REGISTER_KEY(Key::Period);
  REGISTER_KEY(Key::Slash);

  REGISTER_KEY(Key::D0);
  REGISTER_KEY(Key::D1);
  REGISTER_KEY(Key::D2);
  REGISTER_KEY(Key::D3);
  REGISTER_KEY(Key::D4);
  REGISTER_KEY(Key::D5);
  REGISTER_KEY(Key::D6);
  REGISTER_KEY(Key::D7);
  REGISTER_KEY(Key::D8);
  REGISTER_KEY(Key::D9);

  REGISTER_KEY(Key::Semicolon);
  REGISTER_KEY(Key::Equal);

  REGISTER_KEY(Key::A);
  REGISTER_KEY(Key::B);
  REGISTER_KEY(Key::C);
  REGISTER_KEY(Key::D);
  REGISTER_KEY(Key::E);
  REGISTER_KEY(Key::F);
  REGISTER_KEY(Key::G);
  REGISTER_KEY(Key::H);
  REGISTER_KEY(Key::I);
  REGISTER_KEY(Key::J);
  REGISTER_KEY(Key::K);
  REGISTER_KEY(Key::L);
  REGISTER_KEY(Key::M);
  REGISTER_KEY(Key::N);
  REGISTER_KEY(Key::O);
  REGISTER_KEY(Key::P);
  REGISTER_KEY(Key::Q);
  REGISTER_KEY(Key::R);
  REGISTER_KEY(Key::S);
  REGISTER_KEY(Key::T);
  REGISTER_KEY(Key::U);
  REGISTER_KEY(Key::V);
  REGISTER_KEY(Key::W);
  REGISTER_KEY(Key::X);
  REGISTER_KEY(Key::Y);
  REGISTER_KEY(Key::Z);

  REGISTER_KEY(Key::LeftBracket);
  REGISTER_KEY(Key::Backslash);
  REGISTER_KEY(Key::RightBracket);
  REGISTER_KEY(Key::GraveAccent);

  REGISTER_KEY(Key::World1);
  REGISTER_KEY(Key::World2);

  REGISTER_KEY(Key::Escape);
  REGISTER_KEY(Key::Enter);
  REGISTER_KEY(Key::Tab);
  REGISTER_KEY(Key::Backspace);
  REGISTER_KEY(Key::Insert);
  REGISTER_KEY(Key::Delete);
  REGISTER_KEY(Key::Right);
  REGISTER_KEY(Key::Left);
  REGISTER_KEY(Key::Down);
  REGISTER_KEY(Key::Up);
  REGISTER_KEY(Key::PageUp);
  REGISTER_KEY(Key::PageDown);
  REGISTER_KEY(Key::Home);
  REGISTER_KEY(Key::End);
  REGISTER_KEY(Key::CapsLock);
  REGISTER_KEY(Key::ScrollLock);
  REGISTER_KEY(Key::NumLock);
  REGISTER_KEY(Key::PrintScreen);
  REGISTER_KEY(Key::Pause);
  REGISTER_KEY(Key::F1);
  REGISTER_KEY(Key::F2);
  REGISTER_KEY(Key::F3);
  REGISTER_KEY(Key::F4);
  REGISTER_KEY(Key::F5);
  REGISTER_KEY(Key::F6);
  REGISTER_KEY(Key::F7);
  REGISTER_KEY(Key::F8);
  REGISTER_KEY(Key::F9);
  REGISTER_KEY(Key::F10);
  REGISTER_KEY(Key::F11);
  REGISTER_KEY(Key::F12);
  REGISTER_KEY(Key::F13);
  REGISTER_KEY(Key::F14);
  REGISTER_KEY(Key::F15);
  REGISTER_KEY(Key::F16);
  REGISTER_KEY(Key::F17);
  REGISTER_KEY(Key::F18);
  REGISTER_KEY(Key::F19);
  REGISTER_KEY(Key::F20);
  REGISTER_KEY(Key::F21);
  REGISTER_KEY(Key::F22);
  REGISTER_KEY(Key::F23);
  REGISTER_KEY(Key::F24);
  REGISTER_KEY(Key::F25);
  REGISTER_KEY(Key::KP0);
  REGISTER_KEY(Key::KP1);
  REGISTER_KEY(Key::KP2);
  REGISTER_KEY(Key::KP3);
  REGISTER_KEY(Key::KP4);
  REGISTER_KEY(Key::KP5);
  REGISTER_KEY(Key::KP6);
  REGISTER_KEY(Key::KP7);
  REGISTER_KEY(Key::KP8);
  REGISTER_KEY(Key::KP9);
  REGISTER_KEY(Key::KPDecimal);
  REGISTER_KEY(Key::KPDivide);
  REGISTER_KEY(Key::KPMultiply);
  REGISTER_KEY(Key::KPSubtract);
  REGISTER_KEY(Key::KPAdd);
  REGISTER_KEY(Key::KPEnter);
  REGISTER_KEY(Key::KPEqual);

  REGISTER_KEY(Key::LeftShift);
  REGISTER_KEY(Key::LeftControl);
  REGISTER_KEY(Key::LeftAlt);
  REGISTER_KEY(Key::LeftSuper);
  REGISTER_KEY(Key::RightShift);
  REGISTER_KEY(Key::RightControl);
  REGISTER_KEY(Key::RightAlt);
  REGISTER_KEY(Key::RightSuper);
  REGISTER_KEY(Key::Menu);

  // Reverses s_KeyMapWin32ToDT and store into s_KeyMapDTToWin32
  for (const auto &keyValuePair : s_KeyMapDTToWin32) {
    // keyValuePair.second is the value of the collection
    // first is the key
    s_KeyMapWin32ToDT[keyValuePair.second] = keyValuePair.first;
  }
}

#define REGISTER_BUTTON(button) s_MouseMapDTToWin32[button] = Win32::button

void Destiny::WindowsInput::initializeMouseMap() {
  REGISTER_BUTTON(Mouse::Button0);
  REGISTER_BUTTON(Mouse::Button1);
  REGISTER_BUTTON(Mouse::Button2);
  REGISTER_BUTTON(Mouse::Button3);
  REGISTER_BUTTON(Mouse::Button4);
  REGISTER_BUTTON(Mouse::Button5);
  REGISTER_BUTTON(Mouse::Button6);
  REGISTER_BUTTON(Mouse::Button7);

  REGISTER_BUTTON(Mouse::ButtonLast);
  REGISTER_BUTTON(Mouse::ButtonLeft);
  REGISTER_BUTTON(Mouse::ButtonRight);
  REGISTER_BUTTON(Mouse::ButtonMiddle);

  // Reverses vkToDtMouseCode and store into dtMouseCodeToVk
  for (const auto &keyValuePair : s_MouseMapDTToWin32) {
    // keyValuePair.second is the value of the collection
    // first is the key
    s_MouseMapWin32ToDT[keyValuePair.second] = keyValuePair.first;
  }
}

Destiny::KeyCode Destiny::WindowsInput::keyMapWin32ToDT(Win32KeyCode kc) {
  if (s_KeyMapWin32ToDT.contains(kc)) {
    return s_KeyMapWin32ToDT[kc];
  }
  return Key::Unknown;
}

Destiny::Win32KeyCode Destiny::WindowsInput::keyMapDTToWin32(KeyCode kc) {
  if (s_KeyMapDTToWin32.contains(kc)) {
    return s_KeyMapDTToWin32[kc];
  }
  return Win32::Key::Unknown;
}

Destiny::MouseCode Destiny::WindowsInput::mouseMapWin32ToDT(Win32MouseCode mc) {
  if (s_MouseMapWin32ToDT.contains(mc))
    return s_MouseMapWin32ToDT[mc];
  return Mouse::ButtonUnknown;
}

Destiny::Win32MouseCode Destiny::WindowsInput::mouseMapDTToWin32(MouseCode mc) {
  if (s_MouseMapDTToWin32.contains(mc))
    return s_MouseMapDTToWin32[mc];
  return Win32::Mouse::ButtonUnknown;
}

WPARAM Destiny::WindowsInput::mapLeftRightKeys(WPARAM vk, LPARAM lParam) {
  WPARAM new_vk = vk;
  UINT scancode = (lParam & 0x00ff0000) >> 16;
  uint8_t extended = (lParam & 0x01000000) != 0;

  switch (vk) {
  case VK_SHIFT:
    new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
    break;
  case VK_CONTROL:
    new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
    break;
  case VK_MENU:
    new_vk = extended ? VK_RMENU : VK_LMENU;
    break;
  default:
    // not a key we map from generic to left/right specialized
    //  just return it.
    new_vk = vk;
    break;
  }

  return new_vk;
}
