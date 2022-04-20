#pragma once

namespace Destiny {
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() {}

		virtual void swap() = 0;

		virtual bool isVSync() = 0;
		virtual void setVSync(bool enabled) = 0;
	protected:
		bool m_VSync;
	};
}
