// TODO: Add platform macros and surround window class with it

#include "WindowsWindow.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/Events/KeyboardEvent.hpp"
#include "Destiny/Events/MouseEvent.hpp"
#include "Destiny/Platform/D3D11/D3D11Context.hpp"

#include <backends/imgui_impl_win32.h>

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

Destiny::WindowsWindow::Win32WinClass Destiny::WindowsWindow::Win32WinClass::winClass;

Destiny::Window* Destiny::Window::create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

const wchar_t* Destiny::WindowsWindow::Win32WinClass::getName()
{
	return winClassName;
}

HINSTANCE Destiny::WindowsWindow::Win32WinClass::getInstance()
{
	return winClass.hInst;
}

// Create Win32 window class
Destiny::WindowsWindow::Win32WinClass::Win32WinClass()
	: hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEXW wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = handleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = getInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszClassName = getName();
	wc.hIconSm = nullptr;
	RegisterClassExW(&wc);
}

Destiny::WindowsWindow::Win32WinClass::~Win32WinClass()
{
	UnregisterClassW(getName(), getInstance());
}

Destiny::WindowsWindow::WindowsWindow(const WindowProps& props)
	: m_Width(props.width), m_Height(props.height)
{
	DWORD style = WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION | WS_SIZEBOX | WS_OVERLAPPED;

	RECT wr;
	wr.left = 100;
	wr.top = 100;
	wr.bottom = wr.top + m_Height;
	wr.right = wr.left + m_Width;
	AdjustWindowRect(&wr, style, FALSE);

	m_Handle = CreateWindowExW(
		0, Win32WinClass::getName(), props.title.c_str(),
		style,
		300, 300, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, Win32WinClass::getInstance(), this
	);
	ShowWindow(m_Handle, SW_SHOWDEFAULT);
	UpdateWindow(m_Handle);

	m_Context = new D3D11Context(m_Handle);
}

Destiny::WindowsWindow::~WindowsWindow()
{
	delete m_Context;
	DestroyWindow(m_Handle);
}

void Destiny::WindowsWindow::onUpdate()
{
	MSG msg;
	if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		//DT_CORE_TRACE("Before DispatchMessageW()");
		DispatchMessageW(&msg);
		//DT_CORE_TRACE("After DispatchMessageW()");
	};
}

void Destiny::WindowsWindow::initImGuiImpl()
{
	ImGui_ImplWin32_Init(m_Handle);
}

void Destiny::WindowsWindow::imGuiNewFrame()
{
	ImGui_ImplWin32_NewFrame();
}

void Destiny::WindowsWindow::destroyImGuiImpl()
{
	ImGui_ImplWin32_Shutdown();
}

void Destiny::WindowsWindow::setEventListener(EventListener& listener)
{
	m_Listener = &listener;
}

LRESULT __stdcall Destiny::WindowsWindow::handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_NCCREATE)
	{
		const CREATESTRUCTW* const create = reinterpret_cast<CREATESTRUCTW*>(lParam);
		WindowsWindow* const window = reinterpret_cast<WindowsWindow*>(create->lpCreateParams);
		SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtrW(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsWindow::handleMsgMain));
		return window->handleMsg(hWnd, msg, wParam, lParam);
	}
	return DefWindowProcW(hWnd, msg, wParam, lParam);
}

LRESULT __stdcall Destiny::WindowsWindow::handleMsgMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	WindowsWindow* const window = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
	return window->handleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Destiny::WindowsWindow::handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static KeyCode currentTrackingKey;
	static unsigned int keyRepeatCount;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
		return true;
	}

	switch (msg)
	{
	case WM_SIZE:
		if (m_Context != nullptr && wParam != SIZE_MINIMIZED)
		{
			m_Context->resize(LOWORD(lParam), HIWORD(lParam));
		}
		if (m_Listener)
		{
			WindowResizeEvent e(LOWORD(lParam), HIWORD(lParam));
			m_Listener->onEvent(e);
		}
		break;
	case WM_KEYDOWN:
		if (currentTrackingKey != wParam)
		{
			keyRepeatCount = 0;
			currentTrackingKey = wParam;
		}

		keyRepeatCount++;
		if (m_Listener)
		{
			KeyPressEvent e(wParam, keyRepeatCount);
			m_Listener->onEvent(e);
			
		}
		break;
	case WM_KEYUP:
		keyRepeatCount = 0;
		if (m_Listener)
		{
			KeyReleaseEvent e(wParam);
			m_Listener->onEvent(e);
		}
		break;
	case WM_CHAR:
		if (m_Listener)
		{
			KeyTypeEvent e(wParam);
			m_Listener->onEvent(e);
		}
		break;
	case WM_MOUSEMOVE:
		if (m_Listener)
		{
			MouseMoveEvent e(LOWORD(lParam), HIWORD(lParam));
			m_Listener->onEvent(e);
		}
		break;
	case WM_MOUSEWHEEL:
		if (m_Listener)
		{
			MouseScrollEvent e(0, HIWORD(wParam));
			m_Listener->onEvent(e);
		}
		break;
	case WM_LBUTTONDOWN:
		if (m_Listener)
		{
			MouseButtonPressEvent e(Mouse::ButtonLeft);
			m_Listener->onEvent(e);
		}
		break;
	case WM_LBUTTONUP:
		if (m_Listener)
		{
			MouseButtonReleaseEvent e(Mouse::ButtonLeft);
			m_Listener->onEvent(e);
		}
		break;
	case WM_RBUTTONDOWN:
		if (m_Listener)
		{
			MouseButtonPressEvent e(Mouse::ButtonRight);
			m_Listener->onEvent(e);
		}
		break;
	case WM_RBUTTONUP:
		if (m_Listener)
		{
			MouseButtonReleaseEvent e(Mouse::ButtonRight);
			m_Listener->onEvent(e);
		}
		break;
	case WM_MBUTTONDOWN:
		if (m_Listener)
		{
			MouseButtonPressEvent e(Mouse::ButtonMiddle);
			m_Listener->onEvent(e);
		}
		break;
	case WM_MBUTTONUP:
		if (m_Listener)
		{
			MouseButtonReleaseEvent e(Mouse::ButtonMiddle);
			m_Listener->onEvent(e);
		}
		break;
	case WM_CLOSE:
	{
		if (m_Listener) {
			WindowCloseEvent event;
			m_Listener->onEvent(event);
		}
		break;
	}
	default:
		break;
	}

	return DefWindowProcW(hWnd, msg, wParam, lParam);
}
