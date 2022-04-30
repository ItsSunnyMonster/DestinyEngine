#pragma once

#include "Destiny/Exception.hpp"

namespace Destiny
{
	class Win32Exception : public Destiny::Exception
	{
	public:
		Win32Exception(uint16_t line, const char* file, HRESULT hr);
		const char* what() const override;
		const char* getType() const override;
		static std::string translateErrorCode(HRESULT hr);
		HRESULT getErrorCode() const;
		std::string getErrorString() const;
	private:
		HRESULT m_Hr;
	};
}

#define DT_W32_EXCEPT(hr) ::Destiny::Win32Exception(__LINE__, __FILE__, hr)
#define DT_W32_LAST_EXCEPT() ::Destiny::Win32Exception(__LINE__, __FILE__, GetLastError())