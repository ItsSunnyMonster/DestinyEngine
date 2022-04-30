#pragma once

#include "Destiny/Platform/Windows/Win32Exception.hpp"

namespace Destiny
{
	class D3D11Exception : public Win32Exception
	{
	public:
		D3D11Exception(uint16_t line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {});
		const char* getType() const override;
		const std::string& getErrorInfo() const;

		const char* what() const override;

	private:
		std::string m_Info;
	};

	class D3D11DeviceRemovedException : public D3D11Exception
	{
	public:
		D3D11DeviceRemovedException(uint16_t, const char*, HRESULT);

		const char* what() const override;
		const char* getType() const override;

		inline HRESULT getReason() const { return m_Reason; }
	private:
		HRESULT m_Reason;
	};

	class D3D11InfoOnlyException : public Exception
	{
	public:
		D3D11InfoOnlyException(uint16_t line, const char* file, std::vector<std::string> infoMsgs = {});

		const char* getType() const override;
		const char* what() const override;
		const std::string& getErrorInfo() const;
		
	private:
		std::string m_Info;
	};
}

#define DT_D3D11_THROW_NOINFO(hr) { const HRESULT refHr = hr; if(FAILED(refHr)) throw ::Destiny::D3D11Exception(__LINE__, __FILE__, refHr); }

#ifdef DT_DEBUG
#define DT_D3D11_THROW_FAILED(hr) { m_InfoManager.set(); const HRESULT refHr = hr; if (FAILED(refHr)) throw ::Destiny::D3D11Exception(__LINE__, __FILE__, refHr, m_InfoManager.getMessages()); }
#else
#define DT_D3D11_THROW_FAILED(hr) DT_D3D11_THROW_NOINFO(hr)
#endif

#define DT_D3D11_DEVICE_REMOVED_EXCEPTION(reason) ::Destiny::D3D11DeviceRemovedException(__LINE__, __FILE__, reason);

#ifdef DT_DEBUG
#define DT_D3D11_THROW_INFO_ONLY(call) m_InfoManager.set(); (call); { auto v = m_InfoManager.getMessages(); if (!v.empty()) throw ::Destiny::D3D11InfoOnlyException(__LINE__, __FILE__, v); }
#else
#define DT_D3D11_THROW_INFO_ONLY(call)
#endif