/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#include <DestinyEngine.hpp>

class TestLayer : public Destiny::Layer {
public:
	TestLayer()
		: Layer("Test") {}

	void onUpdate() override {
		DT_INFO("TestLayer::onUpdate");
	}

	void onEvent(Destiny::Event& event) override {
		DT_INFO("{0}", event);
	}
};

class SandboxApp : public Destiny::Application {
public:
	SandboxApp() {
		pushLayer(new TestLayer());
	}
	~SandboxApp() override = default;
};

Destiny::Application *Destiny::createApplication() {
	return new SandboxApp();
}
