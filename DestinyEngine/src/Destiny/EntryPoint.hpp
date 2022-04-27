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
		const size_t size = strlen(e.what()) + 1;
		std::wstring wc(size, L'#');
		mbstowcs(&wc[0], e.what(), size);
		TaskDialog(nullptr, nullptr, L"Destiny Exception Thrown!", L"Destiny Exception", &wc[0], TDCBF_OK_BUTTON, TD_ERROR_ICON, nullptr);
	}
	catch (const std::exception& e)
	{
		const size_t size = strlen(e.what()) + 1;
		std::wstring wc(size, L'#');
		mbstowcs(&wc[0], e.what(), size);
		TaskDialog(nullptr, nullptr, L"Standard Exception Thrown!", L"Standard Exception", &wc[0], TDCBF_OK_BUTTON, TD_ERROR_ICON, nullptr);
	}
	catch (...)
	{
		TaskDialog(nullptr, nullptr, L"Unknown Exception Thrown!", L"Unknown Exception", L"No further information.", TDCBF_OK_BUTTON, TD_ERROR_ICON, nullptr);
	}
	return -1;
}
#endif // DT_RELEASE

#endif // DT_PLATFORM_WINDOWS
