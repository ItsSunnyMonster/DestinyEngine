#pragma once

#include "Destiny/KeyCodes.hpp"
#include "Destiny/MouseCodes.hpp"

namespace Destiny
{
	class Input
	{
	public:
		inline static bool isKeyPressed(KeyCode keyCode) { return s_Instance->_isKeyPressed(keyCode); }
		inline static bool isMouseButtonPressed(MouseCode button) { return s_Instance->_isMouseButtonPressed(button); }
		inline static std::pair<float, float> getMousePosition() { return s_Instance->_getMousePosition(); }
		inline static float getMouseX() { return getMousePosition().first; }
		inline static float getMouseY() { return getMousePosition().second; }
	protected:
		virtual bool _isKeyPressed(KeyCode keyCode) = 0;
		virtual bool _isMouseButtonPressed(MouseCode button) = 0;
		virtual std::pair<float, float> _getMousePosition() = 0;
	private:
		static Input* s_Instance;
	};
}
