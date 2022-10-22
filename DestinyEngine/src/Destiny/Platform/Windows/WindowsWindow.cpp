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

#include "WindowsWindow.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/Events/KeyboardEvent.hpp"
#include "Destiny/Events/MouseEvent.hpp"
#include "Destiny/Platform/D3D11/D3D11Context.hpp"
#include "Destiny/Platform/Windows/Win32Exception.hpp"
#include "WindowsInput.hpp"

#include <backends/imgui_impl_win32.h>

// Forward declaration
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg,
                                                      WPARAM wParam,
                                                      LPARAM lParam);

// Static variables
const std::wstring Destiny::WindowsWindow::Win32WinClass::s_WinClassName =
    L"D3D11 WinClass";
Destiny::WindowsWindow::Win32WinClass
    Destiny::WindowsWindow::Win32WinClass::s_WinClass;

Destiny::Window *Destiny::Window::create(const WindowProps &props) {
  return new WindowsWindow(props);
}

const std::wstring &Destiny::WindowsWindow::Win32WinClass::getName() {
  return s_WinClassName;
}

HINSTANCE Destiny::WindowsWindow::Win32WinClass::getInstance() {
  return s_WinClass.hInst;
}

// Create Win32 window class
Destiny::WindowsWindow::Win32WinClass::Win32WinClass()
    : hInst(GetModuleHandle(nullptr)) {
  WNDCLASSEX wc = {0};
  wc.cbSize = sizeof(wc);
  wc.style = CS_CLASSDC;
  wc.lpfnWndProc = handleMsgSetup;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = getInstance();
  wc.hIcon = nullptr;
  wc.hCursor = nullptr;
  wc.hbrBackground = nullptr;
  wc.lpszClassName = getName().c_str();
  wc.hIconSm = nullptr;
  RegisterClassEx(&wc);
}

Destiny::WindowsWindow::Win32WinClass::~Win32WinClass() {
  UnregisterClass(getName().c_str(), getInstance());
}

Destiny::WindowsWindow::WindowsWindow(const WindowProps &props)
    : m_Width(props.width), m_Height(props.height) {
  // throw DT_W32_EXCEPT(ERROR_ARENA_TRASHED);

  ImGui_ImplWin32_EnableDpiAwareness();

  DWORD style = WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION |
                WS_SIZEBOX | WS_OVERLAPPED;

  RECT wr;
  wr.left = 100;
  wr.top = 100;
  wr.bottom = wr.top + m_Height;
  wr.right = wr.left + m_Width;
  if (!AdjustWindowRect(&wr, style, FALSE)) {
    throw DT_W32_LAST_EXCEPT();
  }

  m_Handle = CreateWindowEx(
      0, Win32WinClass::getName().c_str(), DT_PWSTR(props.title.c_str()), style,
      CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
      nullptr, nullptr, Win32WinClass::getInstance(), this);
  if (!m_Handle) {
    throw DT_W32_LAST_EXCEPT();
  }

  ShowWindow(m_Handle, SW_SHOWDEFAULT);
  UpdateWindow(m_Handle);

  m_Context = new D3D11Context(m_Handle, m_Width, m_Height, true);
}

Destiny::WindowsWindow::~WindowsWindow() {
  delete m_Context;
  DestroyWindow(m_Handle);
}

void Destiny::WindowsWindow::onUpdate() {
  MSG msg;
  if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&msg);
    // DT_CORE_TRACE("Before DispatchMessageW()");
    DispatchMessage(&msg);
    // DT_CORE_TRACE("After DispatchMessageW()");
  };
}

void Destiny::WindowsWindow::initImGuiImpl() {
  ImGui_ImplWin32_Init(m_Handle);
  // ImGui_ImplWin32_EnableDpiAwareness();
}

void Destiny::WindowsWindow::imGuiNewFrame() {
  ImGui_ImplWin32_NewFrame();

  ImGuiIO io = ImGui::GetIO();
  float dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(m_Handle);
  io.DisplayFramebufferScale = ImVec2(dpiScale, dpiScale);
  io.DisplaySize.x /= dpiScale;
  io.DisplaySize.y /= dpiScale;

  if (io.MousePos.x != -FLT_MAX && io.MousePos.y != -FLT_MAX) {
    io.MousePos.x /= dpiScale;
    io.MousePos.y /= dpiScale;
  }
}

void Destiny::WindowsWindow::destroyImGuiImpl() { ImGui_ImplWin32_Shutdown(); }

void Destiny::WindowsWindow::setEventListener(EventListener &listener) {
  m_Listener = &listener;
}

void *Destiny::WindowsWindow::getNativeWindow() { return m_Handle; }

LRESULT __stdcall Destiny::WindowsWindow::handleMsgSetup(HWND hWnd, UINT msg,
                                                         WPARAM wParam,
                                                         LPARAM lParam) {
  if (msg == WM_NCCREATE) {
    const CREATESTRUCT *const create = reinterpret_cast<CREATESTRUCT *>(lParam);
    WindowsWindow *const window =
        reinterpret_cast<WindowsWindow *>(create->lpCreateParams);
    SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
    SetWindowLongPtr(hWnd, GWLP_WNDPROC,
                     reinterpret_cast<LONG_PTR>(&WindowsWindow::handleMsgMain));
    return window->handleMsg(hWnd, msg, wParam, lParam);
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT __stdcall Destiny::WindowsWindow::handleMsgMain(HWND hWnd, UINT msg,
                                                        WPARAM wParam,
                                                        LPARAM lParam) {
  WindowsWindow *const window =
      reinterpret_cast<WindowsWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
  return window->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Destiny::WindowsWindow::handleMsg(HWND hWnd, UINT msg, WPARAM wParam,
                                          LPARAM lParam) {
  static KeyCode currentTrackingKey;
  static uint16_t keyRepeatCount;

  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg) {
  case WM_SIZE:
    if (m_Context != nullptr && wParam != SIZE_MINIMIZED) {
      m_Context->resize(LOWORD(lParam), HIWORD(lParam));
    }
    if (m_Listener) {
      WindowResizeEvent e(LOWORD(lParam), HIWORD(lParam));
      m_Listener->onEvent(e);
    }
    break;
  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
      return 0;
    break;
  case WM_SYSKEYDOWN:
  case WM_KEYDOWN:
    if (currentTrackingKey != wParam) {
      keyRepeatCount = 0;
      currentTrackingKey = (KeyCode)wParam;
    }

    keyRepeatCount++;
    if (m_Listener) {
      KeyPressEvent e(WindowsInput::keyMapWin32ToDT(
                          WindowsInput::mapLeftRightKeys(wParam, lParam)),
                      keyRepeatCount);
      m_Listener->onEvent(e);
    }
    break;
  case WM_SYSKEYUP:
  case WM_KEYUP:
    keyRepeatCount = 0;
    if (m_Listener) {
      KeyReleaseEvent e(WindowsInput::keyMapWin32ToDT(
          WindowsInput::mapLeftRightKeys(wParam, lParam)));
      m_Listener->onEvent(e);
    }
    break;
  case WM_CHAR:
    if (m_Listener) {
      KeyTypeEvent e((const char)wParam);
      m_Listener->onEvent(e);
    }
    break;
  case WM_MOUSEMOVE:
    if (m_Listener) {
      MouseMoveEvent e(LOWORD(lParam), HIWORD(lParam));
      m_Listener->onEvent(e);
    }
    break;
  case WM_MOUSEWHEEL:
    if (m_Listener) {
      MouseScrollEvent e(0, HIWORD(wParam));
      m_Listener->onEvent(e);
    }
    break;
  case WM_LBUTTONDOWN:
    if (m_Listener) {
      MouseButtonPressEvent e(Mouse::ButtonLeft);
      m_Listener->onEvent(e);
    }
    break;
  case WM_LBUTTONUP:
    if (m_Listener) {
      MouseButtonReleaseEvent e(Mouse::ButtonLeft);
      m_Listener->onEvent(e);
    }
    break;
  case WM_RBUTTONDOWN:
    if (m_Listener) {
      MouseButtonPressEvent e(Mouse::ButtonRight);
      m_Listener->onEvent(e);
    }
    break;
  case WM_RBUTTONUP:
    if (m_Listener) {
      MouseButtonReleaseEvent e(Mouse::ButtonRight);
      m_Listener->onEvent(e);
    }
    break;
  case WM_MBUTTONDOWN:
    if (m_Listener) {
      MouseButtonPressEvent e(Mouse::ButtonMiddle);
      m_Listener->onEvent(e);
    }
    break;
  case WM_MBUTTONUP:
    if (m_Listener) {
      MouseButtonReleaseEvent e(Mouse::ButtonMiddle);
      m_Listener->onEvent(e);
    }
    break;
  case WM_CLOSE: {
    if (m_Listener) {
      WindowCloseEvent event;
      m_Listener->onEvent(event);
    }
    break;
  }
  case WM_DPICHANGED: {
    if (m_Listener) {
      WindowDPIChangeEvent event(LOWORD(wParam) / 96.0f);
      m_Listener->onEvent(event);
    }
    break;
  }
  default:
    break;
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

float Destiny::WindowsWindow::getDPIScale() const {
  return ImGui_ImplWin32_GetDpiScaleForHwnd(m_Handle);
}
