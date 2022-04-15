/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#include <iostream>
#include "Application.hpp"

namespace Destiny {
    Application::Application() = default;

    Application::~Application() = default;

    void Application::run() {
        for (int i = 0; i < 10; ++i) {
            std::cout << i << std::endl;
        }
    }
}
