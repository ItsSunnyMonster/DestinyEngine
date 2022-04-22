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

		inline std::shared_ptr<Window> getWindow() { return m_Window; }

		inline static Application* get() { return s_Instance; }
	private:
		bool m_Running;
		std::shared_ptr<Window> m_Window;
		Layer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	private:
		bool onWindowCloseEvent(WindowCloseEvent& e);
	};

	// To be defined in CLIENT
	Application* createApplication();
}