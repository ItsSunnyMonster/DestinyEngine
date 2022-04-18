/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#pragma once

#include "Window.hpp"
#include "Destiny/Events/EventListener.hpp"
#include "Destiny/Events/WindowEvent.hpp"

namespace Destiny {
	class Application : public EventListener {
	public:
		Application();
		virtual ~Application();
		void run();
		void onEvent(Event& event) override;
	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
	private:
		bool onWindowCloseEvent(WindowCloseEvent& e);
	};

	// To be defined in CLIENT
	Application* createApplication();
}