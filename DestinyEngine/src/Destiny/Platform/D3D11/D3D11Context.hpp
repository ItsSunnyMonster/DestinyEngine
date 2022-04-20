#pragma once

#include "Destiny/Renderer/GraphicsContext.hpp"

#include <wrl.h>

namespace Destiny {
	class D3D11Context : public GraphicsContext {
	public:
		D3D11Context(HWND hWnd);
		~D3D11Context() override {}

		void swap() override;
		bool isVSync() override;
		void setVSync(bool enabled) override;
	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_D3D11Device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_D3D11SwapChain;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_D3D11Context;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_D3D11Target;
	};
}