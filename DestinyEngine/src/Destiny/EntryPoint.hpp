/*-------------------------------------
 - Copyright (c) ItsSunnyMonster 2022 -
 -------------------------------------*/

//
// Created by ItsSunnyMonster on 14/04/22.
//

#pragma once

#include <Windows.h>

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

#ifdef DT_DEBUG
int main() 
{
	try
	{
		return entry();
	}
	catch (const Destiny::Exception& e)
	{
		DT_CORE_CRITICAL("Destiny Exception Thrown!\n{0}", e.what());
	}
	catch (const std::exception& e)
	{
		DT_CORE_CRITICAL("Standard Exception Thrown!\n{0}", e.what());
	}
	catch (...)
	{
		DT_CORE_CRITICAL("Uknown Exception Thrown!\n{0}", "No further information.");
	}
	return -1;
}
#endif // DT_DEBUG

#ifdef DT_RELEASE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) 
{
	try
	{
		return entry();
	}
	catch (const Destiny::Exception& e)
	{
		MessageBox(nullptr, e.what(), "Destiny Exception Thrown!", MB_ICONERROR | MB_OK);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception Thrown!", MB_ICONERROR | MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, "No further information", "Unknown Exception Thrown!", MB_ICONERROR | MB_OK);
	}
	return -1;
}
#endif // DT_RELEASE

#endif // DT_PLATFORM_WINDOWS
