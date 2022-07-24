#pragma once

#include "Destiny/Window.hpp"

#include "Destiny/KeyCodes.hpp"

#include "Destiny/Exception.hpp"

namespace Destiny 
{

	class WindowsWindow : public Window
	{
	private:
		// This class should only be a singleton (It manages Win32 window classes)
		class Win32WinClass 
		{
		public:
			static const std::wstring& getName();
			static HINSTANCE getInstance();
		private:
			Win32WinClass();
			~Win32WinClass();
			Win32WinClass(const Win32WinClass&) = delete;
			Win32WinClass& operator=(const Win32WinClass&) = delete;
			static const std::wstring s_WinClassName;
			static Win32WinClass s_WinClass;
			HINSTANCE hInst;
		};
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;
		WindowsWindow(const WindowsWindow&) = delete;
		WindowsWindow& operator=(const WindowsWindow&) = delete;

		void onUpdate() override;
		inline uint16_t getWidth() const override { return m_Width; }
		inline uint16_t getHeight() const override { return m_Height; }
		GraphicsContext* getContext() override { return m_Context; }
		void initImGuiImpl() override;
		void imGuiNewFrame() override;
		void destroyImGuiImpl() override;

		void setEventListener(EventListener& listener) override;

		void* getNativeWindow() override;
	private:
		uint16_t m_Width;
		uint16_t m_Height;
		HWND m_Handle;
	private:
		static LRESULT WINAPI handleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI handleMsgMain(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT handleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		EventListener* m_Listener = nullptr;
	};

}
