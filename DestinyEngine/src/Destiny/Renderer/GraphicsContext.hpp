#pragma once

namespace Destiny {
	class GraphicsContext {
	public:
		virtual ~GraphicsContext() {}

		virtual void swap() = 0;

		virtual bool isVSync() = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual void resize(unsigned int width, unsigned int height) = 0;

		virtual void initImGuiImpl() = 0;
		virtual void imGuiNewFrame() = 0;
		virtual void destroyImGuiImpl() = 0;
		virtual void imGuiRender() = 0;

		virtual void clear() = 0;
	protected:
		bool m_VSync;
	};
}
