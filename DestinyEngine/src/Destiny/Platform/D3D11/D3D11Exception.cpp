#include "D3D11Exception.hpp"

Destiny::D3D11Exception::D3D11Exception(
    uint16_t line, const char *file, HRESULT hr,
    std::vector<std::string> infoMsgs /*= {}*/)
    : Win32Exception(line, file, hr) {
  for (const std::string &msg : infoMsgs) {
    m_Info += msg;
    m_Info.push_back('\n');
  }
  if (!m_Info.empty()) {
    m_Info.pop_back();
  } else {
    m_Info = "No information provided.";
  }
}

const char *Destiny::D3D11Exception::getType() const {
  return "Destiny D3D11 Exception";
}

const std::string &Destiny::D3D11Exception::getErrorInfo() const {
  return m_Info;
}

const char *Destiny::D3D11Exception::what() const noexcept {
  std::ostringstream oss;
  oss << getType() << std::endl
      << "[Error Code] 0x" << std::hex << std::uppercase << getErrorCode()
      << std::endl
      << "[Description] " << getErrorString() << std::endl
      << "[Info Log] " << getErrorInfo() << std::endl
      << std::endl
      << getOriginString();
  m_WhatBuffer = oss.str();
  return m_WhatBuffer.c_str();
}

Destiny::D3D11DeviceRemovedException::D3D11DeviceRemovedException(
    uint16_t line, const char *file, HRESULT reason)
    : D3D11Exception(line, file, reason) {}

char const *Destiny::D3D11DeviceRemovedException::what() const noexcept {
  std::ostringstream oss;
  oss << getType() << std::endl
      << "[Reason] " << translateErrorCode(getReason()) << std::endl
      << getOriginString();
  m_WhatBuffer = oss.str();
  return m_WhatBuffer.c_str();
}

const char *Destiny::D3D11DeviceRemovedException::getType() const {
  return "Destiny D3D11 Device Removed Exception";
}

Destiny::D3D11InfoOnlyException::D3D11InfoOnlyException(
    uint16_t line, const char *file, std::vector<std::string> infoMsgs /*= {}*/)
    : Exception(line, file) {
  for (const std::string &msg : infoMsgs) {
    m_Info += msg;
    m_Info.push_back('\n');
  }
  if (!m_Info.empty()) {
    m_Info.pop_back();
  } else {
    m_Info = "No information provided.";
  }
}

const char *Destiny::D3D11InfoOnlyException::getType() const {
  return "Destiny D3D11 Info Only Exception";
}

const char *Destiny::D3D11InfoOnlyException::what() const noexcept {
  std::ostringstream oss;
  oss << getType() << std::endl
      << "[Info Log] " << getErrorInfo() << std::endl
      << std::endl
      << getOriginString();
  m_WhatBuffer = oss.str();
  return m_WhatBuffer.c_str();
}

const std::string &Destiny::D3D11InfoOnlyException::getErrorInfo() const {
  return m_Info;
}
