/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#include "Application.hpp"
#include "Log.hpp"
#include "Destiny/Events/WindowEvent.hpp"
#include "Destiny/Events/KeyboardEvent.hpp"
#include "Destiny/Events/MouseEvent.hpp"
#include "Macros.hpp"

namespace Destiny {
	Application::Application()
		: m_Running(true) {
		m_Window = std::unique_ptr<Window>(Window::create());
		m_Window->setEventListener(*this);
	}

	Application::~Application() = default;

	void Application::run() {
		while (m_Running)
		{
			m_Window->onUpdate();
		}
	}

	void Application::onEvent(Event& event)
	{
		EventDispatcher dispatcher = EventDispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowCloseEvent));
	}

	bool Application::onWindowCloseEvent(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
