#pragma once

#include "Destiny/Events/Event.hpp"

namespace Destiny 
{

	class EventListener
	{
	public:
		virtual void onEvent(Event& event) = 0;
	};

}

