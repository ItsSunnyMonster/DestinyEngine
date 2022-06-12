#include "DxgiInfoManager.hpp"

#include "Destiny/Platform/Windows/Win32Exception.hpp"
#include "Destiny/Platform/D3D11/D3D11Exception.hpp"

#pragma comment(lib, "dxguid.lib")

Destiny::DxgiInfoManager::DxgiInfoManager()
{
	// Define function signature of DXGIGetDebugInterface
	using DXGIGetDebugInterface = HRESULT(WINAPI*)(REFIID, void**);

	// Load the dll that contains the function DXGIGetDebugInterface
	const auto dxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	if (dxgiDebug == nullptr)
	{
		throw DT_W32_LAST_EXCEPT();
	}

	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(dxgiDebug, "DXGIGetDebugInterface")));
	if (DxgiGetDebugInterface == nullptr)
	{
		throw DT_W32_LAST_EXCEPT();
	}

	DT_D3D11_THROW_NOINFO(DxgiGetDebugInterface(__uuidof(IDXGIInfoQueue), reinterpret_cast<void**>(m_DxgiInfoQueue.ReleaseAndGetAddressOf())));
}

void Destiny::DxgiInfoManager::set()
{
	next = m_DxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> Destiny::DxgiInfoManager::getMessages() const
{
	std::vector<std::string> messages;
	const auto end = m_DxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = next; i < end; ++i)
	{
		HRESULT hr;
		SIZE_T messageLength;

		DT_D3D11_THROW_NOINFO(m_DxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));

		auto bytes = std::make_unique<byte[]>(messageLength);
		auto message = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());

		DT_D3D11_THROW_NOINFO(m_DxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, message, &messageLength));
		messages.emplace_back(message->pDescription);
	}
	return messages;
}
#ifdef DT_DEBUG
Destiny::DxgiInfoManager Destiny::DxgiInfoManager::s_Instance;
#endif

Destiny::DxgiInfoManager::~DxgiInfoManager()
{
}
