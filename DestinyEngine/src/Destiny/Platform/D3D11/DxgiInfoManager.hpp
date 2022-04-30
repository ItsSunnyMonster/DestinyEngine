#pragma once

#include <dxgidebug.h>

namespace Destiny
{
	class DxgiInfoManager
	{
	public:
		DxgiInfoManager();
		~DxgiInfoManager();
		DxgiInfoManager(const DxgiInfoManager&) = delete;
		DxgiInfoManager& operator=(const DxgiInfoManager&) = delete;
		void set();
		std::vector<std::string> getMessages() const;
	private:
		uint64_t next = 0;
		IDXGIInfoQueue* m_DxgiInfoQueue = nullptr;
	};
}
