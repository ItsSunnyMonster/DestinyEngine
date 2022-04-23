/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#pragma once

extern Destiny::Application* Destiny::createApplication();

int entry() 
{
	Destiny::Log::init();

	Destiny::Application* app = Destiny::createApplication();
	app->run();
	delete app;

	return 0;
}

#ifdef DT_PLATFORM_WINDOWS

#if 1
int main() 
{
	return entry();
}
#endif // DT_DEBUG

#if 0
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) 
{
	return entry();
}
#endif

#endif // DT_PLATFORM_WINDOWS
