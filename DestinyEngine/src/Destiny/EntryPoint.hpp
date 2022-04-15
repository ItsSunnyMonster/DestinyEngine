/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#pragma once

extern Destiny::Application *Destiny::createApplication();

int main(int argc, char** argv) {
    Destiny::Application* app = Destiny::createApplication();
    app->run();
    delete app;
}
