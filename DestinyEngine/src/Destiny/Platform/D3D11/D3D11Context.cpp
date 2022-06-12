#include "D3D11Context.hpp"
#include "Destiny/Platform/D3D11/D3D11Exception.hpp"
#include "Destiny/Renderer/Buffer.hpp"

#include <backends/imgui_impl_dx11.h>
#include <imgui.h>

#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

Destiny::D3D11Context::D3D11Context(HWND hWnd, uint16_t width, uint16_t height, bool vSync)
	: GraphicsContext(vSync, width, height)
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
	swapChainDesc.BufferCount = 2;
	swapChainDesc.OutputWindow = hWnd;
	//swapChainDesc.OutputWindow = (HWND)696969;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.Flags = D3D11_CREATE_DEVICE_DEBUG;

	UINT flags = 0;
#ifdef DT_DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	DT_D3D11_THROW_FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		m_SwapChain.ReleaseAndGetAddressOf(),
		m_Device.ReleaseAndGetAddressOf(),
		nullptr,
		m_Context.ReleaseAndGetAddressOf()
	));

	createRenderTarget();
}

Destiny::D3D11Context::~D3D11Context()
{
}

void Destiny::D3D11Context::swap()
{	
	HRESULT hr;

	if (FAILED(hr = m_SwapChain->Present(m_VSync ? 1 : 0, 0)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw DT_D3D11_DEVICE_REMOVED_EXCEPTION(m_Device->GetDeviceRemovedReason());
		}
		
		DT_D3D11_THROW_FAILED(hr);
	}
}

void Destiny::D3D11Context::clear()
{
	const float color[] = { 0.0, 162.0 / 256.0, 237.0 / 256.0, 1.0 };
	m_Context->OMSetRenderTargets(1, m_RenderTarget.GetAddressOf(), nullptr);
	m_Context->ClearRenderTargetView(m_RenderTarget.Get(), color);
	
	// Draw test triangle
	{
		struct Vertex
		{
			float x, y;
			float r, g, b;
		};

		Vertex vertices[] =
		{
			{ -0.5f,  0.5f, 1.0f, 0.0f, 0.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f, 0.0f },
			{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 1.0f, 1.0f, 0.0f },
		};

		BufferLayout layout =
		{
			{ ShaderDataType::Float2, "POSITION" },
			{ ShaderDataType::Float3, "COLOR" }
		};

		Ref<VertexBuffer> vertexBuffer = Ref<VertexBuffer>(VertexBuffer::create(reinterpret_cast<float*>(&vertices), std::size(vertices) * 5, this, layout));
		vertexBuffer->bind();

		// Create index buffer
		uint32_t indices[] =
		{
			0, 1, 2,
			0, 3, 1
		};
		Ref<IndexBuffer> indexBuffer = Ref<IndexBuffer>(IndexBuffer::create(indices, std::size(indices), this));
		indexBuffer->bind();

		// Create vertex shader
		ComRef<ID3D11VertexShader> vertexShader;
		ComRef<ID3DBlob> blob;
		DT_D3D11_THROW_FAILED(D3DReadFileToBlob(L"assets/shaders/hlsl/test_shader_vs.cso", blob.ReleaseAndGetAddressOf()));
		DT_D3D11_THROW_FAILED(m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertexShader.ReleaseAndGetAddressOf()));

		// Bind vertex shader to pipeline
		m_Context->VSSetShader(vertexShader.Get(), nullptr, 0);

		// Input layout
		ComRef<ID3D11InputLayout> inputLayout;
		const D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 2 * sizeof(float), D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		DT_D3D11_THROW_FAILED(m_Device->CreateInputLayout(
			ied,
			(UINT)std::size(ied),
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			inputLayout.ReleaseAndGetAddressOf()
		));

		// Bind input layout to pipeline
		m_Context->IASetInputLayout(inputLayout.Get());

		// Create pixel shader
		ComRef<ID3D11PixelShader> pixelShader;
		DT_D3D11_THROW_FAILED(D3DReadFileToBlob(L"assets/shaders/hlsl/test_shader_fs.cso", blob.ReleaseAndGetAddressOf()));
		DT_D3D11_THROW_FAILED(m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixelShader.ReleaseAndGetAddressOf()));
		blob->Release();

		// Bind pixel shader to pipeline
		m_Context->PSSetShader(pixelShader.Get(), nullptr, 0);

		// Set primitive topology
		m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Setup render viewport
		D3D11_VIEWPORT vp = {};
		vp.Width = m_Width;
		vp.Height = m_Height;
		vp.MinDepth = 0;
		vp.MaxDepth = 1;
		vp.TopLeftX = 0;
		vp.TopLeftY = 0;
		m_Context->RSSetViewports(1, &vp);

		// Draw
		DT_D3D11_THROW_INFO_ONLY(m_Context->DrawIndexed((UINT)std::size(indices), 0, 0));

		indexBuffer->unbind();
	}
}

void Destiny::D3D11Context::createRenderTarget()
{
	ComRef<ID3D11Texture2D> backBuffer;
	DT_D3D11_THROW_FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf())));
	DT_D3D11_THROW_FAILED(m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTarget));
}

void Destiny::D3D11Context::cleanUpRenderTarget()
{
	m_RenderTarget->Release();
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
	if (m_Device != nullptr) 
	{
		cleanUpRenderTarget();
		DT_D3D11_THROW_FAILED(m_SwapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0));
		createRenderTarget();

		m_Width = width;
		m_Height = height;
	}
}

void Destiny::D3D11Context::initImGuiImpl()
{
	ImGui_ImplDX11_Init(m_Device.Get(), m_Context.Get());
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
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
