#pragma once

#include "Destiny/Renderer/GraphicsContext.hpp"
#include "DxgiInfoManager.hpp"

namespace Destiny 
{

	class D3D11Context : public GraphicsContext 
	{
	public:
		D3D11Context(HWND hWnd);
		~D3D11Context() override;

		void swap() override;
		bool isVSync() override;
		void setVSync(bool enabled) override;
		void resize(unsigned int width, unsigned int height) override;

		void initImGuiImpl() override;
		void imGuiNewFrame() override;
		void destroyImGuiImpl() override;
		void imGuiRender() override;
		void clear() override;
	private:
		void createRenderTarget();
		void cleanUpRenderTarget();
	private:
		ID3D11Device* m_Device;
		IDXGISwapChain* m_SwapChain;
		ID3D11DeviceContext* m_Context;
		ID3D11RenderTargetView* m_RenderTarget;
#ifdef DT_DEBUG
		DxgiInfoManager m_InfoManager;
#endif
	};

}