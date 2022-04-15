/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#pragma once

namespace Destiny {
    class Application {
    public:
        Application();
        virtual ~Application();
        void run();
    };

    // To be defined in CLIENT
    Application* createApplication();
}