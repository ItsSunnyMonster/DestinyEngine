#pragma once

#include "Destiny/Events/EventListener.hpp"

namespace Destiny {
	struct WindowProps {
		std::wstring title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::wstring& title = L"Destiny Engine",
			unsigned int width = 600,
			unsigned int height = 400)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	public:
		virtual ~Window() {}
		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		virtual void setEventListener(EventListener& listener) = 0;

		static Window* create(const WindowProps& props = WindowProps());
	};
}
