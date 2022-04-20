#include "D3D11Context.hpp"

using namespace Microsoft::WRL;

Destiny::D3D11Context::D3D11Context(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1; // This actually means 2 buffered (which is weird)
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_D3D11SwapChain,
		&m_D3D11Device,
		nullptr,
		&m_D3D11Context
	);

	ComPtr<ID3D11Resource> backBuffer;
	m_D3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	m_D3D11Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_D3D11Target);
}

void Destiny::D3D11Context::swap()
{
	m_D3D11SwapChain->Present(m_VSync ? 1 : 0, 0);
}

bool Destiny::D3D11Context::isVSync()
{
	return m_VSync;
}

void Destiny::D3D11Context::setVSync(bool enabled)
{
	m_VSync = enabled;
}
