#include "Win32Exception.hpp"

Destiny::Win32Exception::Win32Exception(uint16_t line, const char *file,
                                        HRESULT hr)
    : Destiny::Exception(line, file), m_Hr(hr) {}

const char *Destiny::Win32Exception::what() const noexcept {
  std::ostringstream oss;
  oss << getType() << std::endl
      << "[Error Code] 0x" << std::hex << std::uppercase << getErrorCode()
      << std::endl
      << "[Description] " << getErrorString() << std::endl
      << getOriginString();
  m_WhatBuffer = oss.str();
  return m_WhatBuffer.c_str();
}

const char *Destiny::Win32Exception::getType() const {
  return "Destiny Win32 Exception";
}

std::string Destiny::Win32Exception::translateErrorCode(HRESULT hr) {
  wchar_t *messageBuffer = nullptr;
  DWORD messageLength = FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      reinterpret_cast<LPWSTR>(&messageBuffer), 0, nullptr);
  if (messageLength == 0) {
    std::wstringstream ss;
    ss << L"Unidentified error code " << hr;
    return DT_U8STR(ss.str().c_str());
  }
  std::string errorString = DT_U8STR(messageBuffer);
  LocalFree(messageBuffer);
  return errorString;
}

HRESULT Destiny::Win32Exception::getErrorCode() const { return m_Hr; }

std::string Destiny::Win32Exception::getErrorString() const {
  return translateErrorCode(m_Hr);
}
