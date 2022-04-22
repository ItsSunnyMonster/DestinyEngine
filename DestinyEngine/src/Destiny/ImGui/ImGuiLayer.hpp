#pragma once

#include "Destiny/Layer/Layer.hpp"

namespace Destiny {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(Event& event) override;
		void onImGuiRender() override;
	};
}