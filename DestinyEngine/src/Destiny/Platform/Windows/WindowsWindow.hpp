#pragma once

#include "Destiny/Window.hpp"

namespace Destiny {
	class WindowsWindow : public Window
	{
	private:
		// This class should only be a singleton (It manages Win32 window classes)
		class Win32WinClass {
		public:
			static const wchar_t* getName();
			static HINSTANCE getInstance();
		private:
			Win32WinClass();
			~Win32WinClass();
			Win32WinClass(const Win32WinClass&) = delete;
			Win32WinClass& operator=(const Win32WinClass&) = delete;
			static constexpr const wchar_t* winClassName = L"D3D11 WinClass";
			static Win32WinClass winClass;
			HINSTANCE hInst;
		};
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;

		void onUpdate() override;
		inline unsigned int getWidth() const override { return m_Width; }
		inline unsigned int getHeight() const override { return m_Height; }

		void setEventListener(EventListener& listener) override;
	private:
		unsigned int m_Width;
		unsigned int m_Height;
		HWND m_Handle;
	private:
		static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI handleMsgMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		EventListener* m_Listener = nullptr;
	// TEMPORARY
	private:
		IDXGISwapChain* m_SwapChain = nullptr;
		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_Context = nullptr;
		ID3D11RenderTargetView* m_Target = nullptr;
	};
}
