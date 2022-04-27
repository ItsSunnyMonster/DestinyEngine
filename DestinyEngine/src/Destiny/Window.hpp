#pragma once

#include "Destiny/Events/EventListener.hpp"

#include "Destiny/Renderer/GraphicsContext.hpp"

namespace Destiny 
{

	struct WindowProps 
	{
		std::string title;
		uint16_t width;
		uint16_t height;

		WindowProps(const std::string& title = "Destiny Engine",
			uint16_t width = 800,
			uint16_t height = 600)
			: title(title), width(width), height(height) {}
	};

	class Window
	{
	public:
		virtual ~Window() {}
		virtual void onUpdate() = 0;

		virtual uint16_t getWidth() const = 0;
		virtual uint16_t getHeight() const = 0;

		virtual void setEventListener(EventListener& listener) = 0;

		virtual GraphicsContext* getContext() = 0;

		virtual void initImGuiImpl() = 0;
		virtual void imGuiNewFrame() = 0;
		virtual void destroyImGuiImpl() = 0;

		virtual void* getNativeWindow() = 0;

		static Window* create(const WindowProps& props = WindowProps());
	protected:
		GraphicsContext* m_Context = nullptr;
	};

}
