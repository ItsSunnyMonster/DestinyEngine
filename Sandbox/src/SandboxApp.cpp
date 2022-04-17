/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#include <DestinyEngine.hpp>
#include <Destiny/EntryPoint.hpp>

class SandboxApp : public Destiny::Application {
public:
	~SandboxApp() override = default;
};

Destiny::Application *Destiny::createApplication() {
	return new SandboxApp();
}
