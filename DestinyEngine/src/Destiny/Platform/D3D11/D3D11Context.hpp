#pragma once

#include "Destiny/Renderer/GraphicsContext.hpp"

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
		ID3D11Device* m_D3D11Device;
		IDXGISwapChain* m_D3D11SwapChain;
		ID3D11DeviceContext* m_D3D11Context;
		ID3D11RenderTargetView* m_D3D11Target;
	};

}