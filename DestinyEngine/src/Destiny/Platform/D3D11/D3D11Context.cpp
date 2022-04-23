#include "D3D11Context.hpp"

#include <backends/imgui_impl_dx11.h>
#include <imgui.h>

Destiny::D3D11Context::D3D11Context(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1; // This actually means 2 buffered (which is weird)
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = D3D11_CREATE_DEVICE_DEBUG;

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

	createRenderTarget();
}

Destiny::D3D11Context::~D3D11Context()
{
	m_D3D11Context->Release();
	m_D3D11Device->Release();
	m_D3D11SwapChain->Release();
	cleanUpRenderTarget();
}

void Destiny::D3D11Context::swap()
{
	m_D3D11SwapChain->Present(m_VSync ? 1 : 0, 0);
}

void Destiny::D3D11Context::clear()
{
	const float color[] = { 1.0, 0.0, 0.0, 1.0 };
	m_D3D11Context->OMSetRenderTargets(1, &m_D3D11Target, nullptr);
	m_D3D11Context->ClearRenderTargetView(m_D3D11Target, color);
}

void Destiny::D3D11Context::createRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	m_D3D11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	m_D3D11Device->CreateRenderTargetView(backBuffer, nullptr, &m_D3D11Target);
	backBuffer->Release();
}

void Destiny::D3D11Context::cleanUpRenderTarget()
{
	m_D3D11Target->Release();
}

bool Destiny::D3D11Context::isVSync()
{
	return m_VSync;
}

void Destiny::D3D11Context::setVSync(bool enabled)
{
	m_VSync = enabled;
}

void Destiny::D3D11Context::resize(unsigned int width, unsigned int height)
{
	if (m_D3D11Device != nullptr) 
	{
		cleanUpRenderTarget();
		m_D3D11SwapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
		createRenderTarget();
	}
}

void Destiny::D3D11Context::initImGuiImpl()
{
	ImGui_ImplDX11_Init(m_D3D11Device, m_D3D11Context);
}

void Destiny::D3D11Context::imGuiNewFrame()
{
	ImGui_ImplDX11_NewFrame();
}

void Destiny::D3D11Context::destroyImGuiImpl()
{
	ImGui_ImplDX11_Shutdown();
}

void Destiny::D3D11Context::imGuiRender()
{
	auto drawData = ImGui::GetDrawData();
	ImGui_ImplDX11_RenderDrawData(drawData);
}
