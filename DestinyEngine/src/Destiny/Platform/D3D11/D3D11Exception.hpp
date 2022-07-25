/*
 *   Copyright (c) 2022 ItsSunnyMonster

 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.

 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "Destiny/Platform/Windows/Win32Exception.hpp"
#include "DxgiInfoManager.hpp"

namespace Destiny {
class D3D11Exception : public Win32Exception {
public:
  D3D11Exception(uint16_t line, const char *file, HRESULT hr,
                 std::vector<std::string> infoMsgs = {});
  const char *getType() const override;
  const std::string &getErrorInfo() const;

  const char *what() const noexcept override;

private:
  std::string m_Info;
};

class D3D11DeviceRemovedException : public D3D11Exception {
public:
  D3D11DeviceRemovedException(uint16_t, const char *, HRESULT);

  const char *what() const noexcept override;
  const char *getType() const override;

  inline HRESULT getReason() const { return m_Reason; }

private:
  HRESULT m_Reason;
};

class D3D11InfoOnlyException : public Exception {
public:
  D3D11InfoOnlyException(uint16_t line, const char *file,
                         std::vector<std::string> infoMsgs = {});

  const char *getType() const override;
  const char *what() const noexcept override;
  const std::string &getErrorInfo() const;

private:
  std::string m_Info;
};
} // namespace Destiny

#define DT_D3D11_THROW_NOINFO(hr)                                              \
  {                                                                            \
    const HRESULT refHr = hr;                                                  \
    if (FAILED(refHr))                                                         \
      throw ::Destiny::D3D11Exception(__LINE__, __FILE__, refHr);              \
  }

#ifdef DT_DEBUG
#define DT_D3D11_THROW_FAILED(hr)                                              \
  {                                                                            \
    ::Destiny::DxgiInfoManager::s_Instance.set();                              \
    const HRESULT refHr = hr;                                                  \
    if (FAILED(refHr))                                                         \
      throw ::Destiny::D3D11Exception(                                         \
          __LINE__, __FILE__, refHr,                                           \
          ::Destiny::DxgiInfoManager::s_Instance.getMessages());               \
  }
#else
#define DT_D3D11_THROW_FAILED(hr) DT_D3D11_THROW_NOINFO(hr)
#endif

#define DT_D3D11_DEVICE_REMOVED_EXCEPTION(reason)                              \
  ::Destiny::D3D11DeviceRemovedException(__LINE__, __FILE__, reason);

#ifdef DT_DEBUG
#define DT_D3D11_THROW_INFO_ONLY(call)                                         \
  ::Destiny::DxgiInfoManager::s_Instance.set();                                \
  (call);                                                                      \
  {                                                                            \
    auto v = ::Destiny::DxgiInfoManager::s_Instance.getMessages();             \
    if (!v.empty())                                                            \
      throw ::Destiny::D3D11InfoOnlyException(__LINE__, __FILE__, v);          \
  }
#else
#define DT_D3D11_THROW_INFO_ONLY(call) call
#endif