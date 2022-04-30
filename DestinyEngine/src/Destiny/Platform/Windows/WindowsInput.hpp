#pragma once

#include "Destiny/Input.hpp"

#include "Win32KeyCodes.hpp"
#include "Win32MouseCodes.hpp"

namespace Destiny
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();
	protected:
		bool _isKeyPressed(KeyCode keyCode) override;

		bool _isMouseButtonPressed(MouseCode button) override;

		std::pair<float, float> _getMousePosition() override;
	private:
		static std::unordered_map<Win32KeyCode, KeyCode> s_KeyMapWin32ToDT;
		static std::unordered_map<KeyCode, Win32KeyCode> s_KeyMapDTToWin32;
		static std::unordered_map<Win32MouseCode, MouseCode> s_MouseMapWin32ToDT;
		static std::unordered_map<MouseCode, Win32MouseCode> s_MouseMapDTToWin32;
		static bool s_MouseCodeInitialized;
		static bool s_KeyMapInitialized;
		static void initializeKeyMap();
		static void initializeMouseMap();
	public:
		static KeyCode keyMapWin32ToDT(Win32KeyCode kc);
		static Win32KeyCode keyMapDTToWin32(KeyCode kc);
		static MouseCode mouseMapWin32ToDT(Win32MouseCode mc);
		static Win32KeyCode mouseMapDTToWin32(MouseCode mc);
		static WPARAM mapLeftRightKeys(WPARAM vk, LPARAM lParam);
	};
}