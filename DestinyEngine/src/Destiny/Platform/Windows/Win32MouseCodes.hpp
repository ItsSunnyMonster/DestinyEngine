#pragma once

namespace Destiny
{
	using Win32MouseCode = WPARAM;
	
	namespace Win32
	{
		namespace Mouse
		{
			enum : Win32MouseCode
			{
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
	}
}
