#pragma once

#include "Destiny/Events/Event.hpp"
#include "Destiny/Events/EventListener.hpp"

namespace Destiny {

	class Layer : public EventListener {
	public:
		Layer(const std::string& name);
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getDebugName() { return m_DebugName; }

		inline void enable() { m_Enabled = true; }
		inline void disable() { m_Enabled = false; }
		// This returns true if the layer is toggled to enable
		inline bool toggle() { m_Enabled = !m_Enabled; return m_Enabled; }
		inline bool isEnabled() { return m_Enabled; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};

}