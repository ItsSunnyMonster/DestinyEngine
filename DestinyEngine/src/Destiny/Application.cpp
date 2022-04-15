/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#include <iostream>
#include "Application.hpp"
#include "Log.hpp"

namespace Destiny {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::run() {
        Log::init();
        DT_CORE_TRACE("Hello?");
        DT_INFO("HELLO!");
    }
}
