/*
 *   Copyright (c) 2022 ItsSunnyMonster

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <Windows.h>

extern Destiny::Application *Destiny::createApplication();

int entry() {
  Destiny::Log::init();

  Destiny::Application *app = Destiny::createApplication();
  app->run();
  delete app;

  return 0;
}

#ifdef DT_PLATFORM_WINDOWS

#ifdef DT_DEBUG
int main() {
  try {
    return entry();
  } catch (const Destiny::Exception &e) {
    DT_CORE_CRITICAL("Destiny Exception Thrown!\n{0}", e.what());
  } catch (const std::exception &e) {
    DT_CORE_CRITICAL("Standard Exception Thrown!\n{0}", e.what());
  } catch (...) {
    DT_CORE_CRITICAL("Uknown Exception Thrown!\n{0}",
                     "No further information.");
  }
  return -1;
}
#endif // DT_DEBUG

#ifdef DT_RELEASE
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine,
                   int nCmdShow) {
  try {
    return entry();
  } catch (const Destiny::Exception &e) {
    TaskDialog(nullptr, nullptr, L"Destiny Exception Thrown!",
               L"Destiny Exception", DT_PWSTR(e.what()), TDCBF_OK_BUTTON, TD_ERROR_ICON,
               nullptr);
  } catch (const std::exception &e) {
    TaskDialog(nullptr, nullptr, L"Standard Exception Thrown!",
               L"Standard Exception", DT_PWSTR(e.what()), TDCBF_OK_BUTTON, TD_ERROR_ICON,
               nullptr);
  } catch (...) {
    TaskDialog(nullptr, nullptr, L"Unknown Exception Thrown!",
               L"Unknown Exception", L"No further information.",
               TDCBF_OK_BUTTON, TD_ERROR_ICON, nullptr);
  }
  return -1;
}
#endif // DT_RELEASE

#endif // DT_PLATFORM_WINDOWS
