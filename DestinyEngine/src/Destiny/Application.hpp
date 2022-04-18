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
#include "Destiny/Layer/LayerStack.hpp"

namespace Destiny {
	class Application : public EventListener {
	public:
		Application();
		virtual ~Application();
		void run();
		void onEvent(Event& event) override;
		void pushLayer(Layer* layer) { m_LayerStack.pushLayer(layer); }
		void pushOverlay(Layer* layer) { m_LayerStack.pushOverlay(layer); }
	private:
		bool m_Running;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
	private:
		bool onWindowCloseEvent(WindowCloseEvent& e);
	};

	// To be defined in CLIENT
	Application* createApplication();
}