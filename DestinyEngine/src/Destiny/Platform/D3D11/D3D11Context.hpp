#pragma once

#include "Destiny/Renderer/GraphicsContext.hpp"
#include "DxgiInfoManager.hpp"

namespace Destiny 
{

	class D3D11Context : public GraphicsContext 
	{
	public:
		D3D11Context(HWND hWnd, uint16_t width, uint16_t height, bool vSync);
		~D3D11Context() override;

		void swap() override;
		bool isVSync() override;
		void setVSync(bool enabled) override;
		void resize(unsigned int width, unsigned int height) override;

		inline ComRef<ID3D11DeviceContext> getD3D11Context() { return m_Context; }
		inline ComRef<ID3D11Device> getD3D11Device() { return m_Device; }
		inline ComRef<IDXGISwapChain> getD3D11SwapChain() { return m_SwapChain; }
		inline ComRef<ID3D11RenderTargetView> getD3D11RenderTarget() { return m_RenderTarget; }

		void initImGuiImpl() override;
		void imGuiNewFrame() override;
		void destroyImGuiImpl() override;
		void imGuiRender() override;
		void clear() override;
	private:
		void createRenderTarget();
		void cleanUpRenderTarget();
	private:
		ComRef<ID3D11Device> m_Device;
		ComRef<IDXGISwapChain> m_SwapChain;
		ComRef<ID3D11DeviceContext> m_Context;
		ComRef<ID3D11RenderTargetView> m_RenderTarget;
	};

}