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

namespace Destiny {
using Win32MouseCode = WPARAM;

namespace Win32 {
namespace Mouse {
enum : Win32MouseCode {
  ButtonUnknown = 0,

  Button0 = VK_LBUTTON,
  Button1 = VK_RBUTTON,
  Button2 = VK_MBUTTON,
  Button3 = VK_XBUTTON1,
  Button4 = VK_XBUTTON2,
  Button5 = ButtonUnknown,
  Button6 = ButtonUnknown,
  Button7 = ButtonUnknown,

  ButtonLast = Button7,
  ButtonLeft = Button0,
  ButtonRight = Button1,
  ButtonMiddle = Button2
};
}
} // namespace Win32
} // namespace Destiny
