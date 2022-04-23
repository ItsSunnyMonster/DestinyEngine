// TODO: Add platform macros and surround window class with it

#include "WindowsWindow.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/Events/KeyboardEvent.hpp"
#include "Destiny/Events/MouseEvent.hpp"
#include "Destiny/Platform/D3D11/D3D11Context.hpp"

#include <backends/imgui_impl_win32.h>

// Forward declaration
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Static variables
Destiny::WindowsWindow::Win32WinClass Destiny::WindowsWindow::Win32WinClass::s_WinClass;
bool Destiny::WindowsWindow::s_KeyMapInitialized = false;
std::unordered_map<WPARAM, Destiny::KeyCode> Destiny::WindowsWindow::s_VkToDtKeyCode;
std::unordered_map<Destiny::KeyCode, WPARAM> Destiny::WindowsWindow::s_DtKeyCodeToVk;

Destiny::Window* Destiny::Window::create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

const wchar_t* Destiny::WindowsWindow::Win32WinClass::getName()
{
	return s_WinClassName;
}

HINSTANCE Destiny::WindowsWindow::Win32WinClass::getInstance()
{
	return s_WinClass.hInst;
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
	if (!s_KeyMapInitialized)
		initializeKeyMap();

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
	if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) 
	{
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

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

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
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_SYSKEYDOWN:
	case WM_KEYDOWN:
		if (currentTrackingKey != wParam)
		{
			keyRepeatCount = 0;
			currentTrackingKey = wParam;
		}

		keyRepeatCount++;
		if (m_Listener)
		{
			KeyPressEvent e(vkToDtKeyCode(mapLeftRightKeys(wParam, lParam)), keyRepeatCount);
			m_Listener->onEvent(e);
			
		}
		break;
	case WM_SYSKEYUP:
	case WM_KEYUP:
		keyRepeatCount = 0;
		if (m_Listener)
		{
			KeyReleaseEvent e(vkToDtKeyCode(mapLeftRightKeys(wParam, lParam)));
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
		if (m_Listener) 
		{
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

void Destiny::WindowsWindow::initializeKeyMap()
{
	s_VkToDtKeyCode[VK_SPACE] = Key::Space;
	s_VkToDtKeyCode[VK_OEM_7] = Key::Apostrophe;
	s_VkToDtKeyCode[VK_OEM_COMMA] = Key::Comma;
	s_VkToDtKeyCode[VK_OEM_MINUS] = Key::Minus;
	s_VkToDtKeyCode[VK_OEM_PERIOD] = Key::Period;
	s_VkToDtKeyCode[VK_OEM_2] = Key::Slash;
	s_VkToDtKeyCode['0'] = Key::D0;
	s_VkToDtKeyCode['1'] = Key::D1;
	s_VkToDtKeyCode['2'] = Key::D2;
	s_VkToDtKeyCode['3'] = Key::D3;
	s_VkToDtKeyCode['4'] = Key::D4;
	s_VkToDtKeyCode['5'] = Key::D5;
	s_VkToDtKeyCode['6'] = Key::D6;
	s_VkToDtKeyCode['7'] = Key::D7;
	s_VkToDtKeyCode['8'] = Key::D8;
	s_VkToDtKeyCode['9'] = Key::D9;
	s_VkToDtKeyCode[VK_OEM_1] = Key::Semicolon;
	s_VkToDtKeyCode[VK_OEM_PLUS] = Key::Equal;
	s_VkToDtKeyCode['A'] = Key::A;
	s_VkToDtKeyCode['B'] = Key::B;
	s_VkToDtKeyCode['C'] = Key::C;
	s_VkToDtKeyCode['D'] = Key::D;
	s_VkToDtKeyCode['E'] = Key::E;
	s_VkToDtKeyCode['F'] = Key::F;
	s_VkToDtKeyCode['G'] = Key::G;
	s_VkToDtKeyCode['H'] = Key::H;
	s_VkToDtKeyCode['I'] = Key::I;
	s_VkToDtKeyCode['J'] = Key::J;
	s_VkToDtKeyCode['K'] = Key::K;
	s_VkToDtKeyCode['L'] = Key::L;
	s_VkToDtKeyCode['M'] = Key::M;
	s_VkToDtKeyCode['N'] = Key::N;
	s_VkToDtKeyCode['O'] = Key::O;
	s_VkToDtKeyCode['P'] = Key::P;
	s_VkToDtKeyCode['Q'] = Key::Q;
	s_VkToDtKeyCode['R'] = Key::R;
	s_VkToDtKeyCode['S'] = Key::S;
	s_VkToDtKeyCode['T'] = Key::T;
	s_VkToDtKeyCode['U'] = Key::U;
	s_VkToDtKeyCode['V'] = Key::V;
	s_VkToDtKeyCode['W'] = Key::W;
	s_VkToDtKeyCode['X'] = Key::X;
	s_VkToDtKeyCode['Y'] = Key::Y;
	s_VkToDtKeyCode['Z'] = Key::Z;
	s_VkToDtKeyCode[VK_OEM_4] = Key::LeftBracket;
	s_VkToDtKeyCode[VK_OEM_5] = Key::Backslash;
	s_VkToDtKeyCode[VK_OEM_6] = Key::RightBracket;
	s_VkToDtKeyCode[VK_OEM_3] = Key::GraveAccent;
	s_VkToDtKeyCode[VK_ESCAPE] = Key::Escape;
	s_VkToDtKeyCode[VK_RETURN] = Key::Enter;
	s_VkToDtKeyCode[VK_TAB] = Key::Tab;
	s_VkToDtKeyCode[VK_BACK] = Key::Backspace;
	s_VkToDtKeyCode[VK_INSERT] = Key::Insert;
	s_VkToDtKeyCode[VK_DELETE] = Key::Delete;
	s_VkToDtKeyCode[VK_RIGHT] = Key::Right;
	s_VkToDtKeyCode[VK_LEFT] = Key::Left;
	s_VkToDtKeyCode[VK_UP] = Key::Up;
	s_VkToDtKeyCode[VK_DOWN] = Key::Down;
	s_VkToDtKeyCode[VK_PRIOR] = Key::PageUp;
	s_VkToDtKeyCode[VK_NEXT] = Key::PageDown;
	s_VkToDtKeyCode[VK_HOME] = Key::Home;
	s_VkToDtKeyCode[VK_END] = Key::End;
	s_VkToDtKeyCode[VK_CAPITAL] = Key::CapsLock;
	s_VkToDtKeyCode[VK_SCROLL] = Key::ScrollLock;
	s_VkToDtKeyCode[VK_NUMLOCK] = Key::NumLock;
	s_VkToDtKeyCode[VK_SNAPSHOT] = Key::PrintScreen;
	s_VkToDtKeyCode[VK_PAUSE] = Key::Pause;
	s_VkToDtKeyCode[VK_F1] = Key::F1;
	s_VkToDtKeyCode[VK_F2] = Key::F2;
	s_VkToDtKeyCode[VK_F3] = Key::F3;
	s_VkToDtKeyCode[VK_F4] = Key::F4;
	s_VkToDtKeyCode[VK_F5] = Key::F5;
	s_VkToDtKeyCode[VK_F6] = Key::F6;
	s_VkToDtKeyCode[VK_F7] = Key::F7;
	s_VkToDtKeyCode[VK_F8] = Key::F8;
	s_VkToDtKeyCode[VK_F9] = Key::F9;
	s_VkToDtKeyCode[VK_F10] = Key::F10;
	s_VkToDtKeyCode[VK_F11] = Key::F11;
	s_VkToDtKeyCode[VK_F12] = Key::F12;
	s_VkToDtKeyCode[VK_F13] = Key::F13;
	s_VkToDtKeyCode[VK_F14] = Key::F14;
	s_VkToDtKeyCode[VK_F15] = Key::F15;
	s_VkToDtKeyCode[VK_F16] = Key::F16;
	s_VkToDtKeyCode[VK_F17] = Key::F17;
	s_VkToDtKeyCode[VK_F18] = Key::F18;
	s_VkToDtKeyCode[VK_F19] = Key::F19;
	s_VkToDtKeyCode[VK_F20] = Key::F20;
	s_VkToDtKeyCode[VK_F21] = Key::F21;
	s_VkToDtKeyCode[VK_F22] = Key::F22;
	s_VkToDtKeyCode[VK_F23] = Key::F23;
	s_VkToDtKeyCode[VK_F24] = Key::F24;
	s_VkToDtKeyCode[VK_NUMPAD0] = Key::KP0;
	s_VkToDtKeyCode[VK_NUMPAD1] = Key::KP1;
	s_VkToDtKeyCode[VK_NUMPAD2] = Key::KP2;
	s_VkToDtKeyCode[VK_NUMPAD3] = Key::KP3;
	s_VkToDtKeyCode[VK_NUMPAD4] = Key::KP4;
	s_VkToDtKeyCode[VK_NUMPAD5] = Key::KP5;
	s_VkToDtKeyCode[VK_NUMPAD6] = Key::KP6;
	s_VkToDtKeyCode[VK_NUMPAD7] = Key::KP7;
	s_VkToDtKeyCode[VK_NUMPAD8] = Key::KP8;
	s_VkToDtKeyCode[VK_NUMPAD9] = Key::KP9;
	s_VkToDtKeyCode[VK_DECIMAL] = Key::KPDecimal;
	s_VkToDtKeyCode[VK_DIVIDE] = Key::KPDivide;
	s_VkToDtKeyCode[VK_MULTIPLY] = Key::KPMultiply;
	s_VkToDtKeyCode[VK_SUBTRACT] = Key::KPSubtract;
	s_VkToDtKeyCode[VK_ADD] = Key::KPAdd;
	s_VkToDtKeyCode[VK_LSHIFT] = Key::LeftShift;
	s_VkToDtKeyCode[VK_LCONTROL] = Key::LeftControl;
	s_VkToDtKeyCode[VK_LMENU] = Key::LeftAlt;
	s_VkToDtKeyCode[VK_LWIN] = Key::LeftSuper;
	s_VkToDtKeyCode[VK_RSHIFT] = Key::RightShift;
	s_VkToDtKeyCode[VK_RCONTROL] = Key::RightControl;
	s_VkToDtKeyCode[VK_RMENU] = Key::RightAlt;
	s_VkToDtKeyCode[VK_RWIN] = Key::RightSuper;

	// Reverses vkToDtKeyCode and store into dtKeyCodeToVk
	for (const auto& keyValuePair : s_VkToDtKeyCode) 
	{
		// keyValuePair.second is the value of the collection
		// first is the key
		s_DtKeyCodeToVk[keyValuePair.second] = keyValuePair.first;
	}
}

Destiny::KeyCode Destiny::WindowsWindow::vkToDtKeyCode(WPARAM vk) 
{
	return s_VkToDtKeyCode[vk];
}

WPARAM Destiny::WindowsWindow::dtKeyCodeToVk(Destiny::KeyCode kc) 
{
	return s_DtKeyCodeToVk[kc];
}

WPARAM Destiny::WindowsWindow::mapLeftRightKeys(WPARAM vk, LPARAM lParam)
{
	WPARAM new_vk = vk;
	UINT scancode = (lParam & 0x00ff0000) >> 16;
	int extended = (lParam & 0x01000000) != 0;

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
