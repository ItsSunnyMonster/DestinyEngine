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

namespace Destiny {
	Application::Application() = default;

	Application::~Application() = default;

	void Application::run() {
		const int x = 0;
		Log::init();
		DT_CORE_TRACE("Hello?");
		DT_INFO("HELLO!");
	}
}
