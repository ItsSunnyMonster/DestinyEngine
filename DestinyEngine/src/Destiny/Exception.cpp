#include "Exception.hpp"

Destiny::Exception::Exception(uint16_t line, const char *file)
    : Exception(line, file, "No message provided.") {}

Destiny::Exception::Exception(uint16_t line, const char *file, const char *msg)
    : m_Line(line), m_File(file), m_Msg(msg) {}

char const *Destiny::Exception::what() const noexcept {
  std::ostringstream oss;
  oss << "[Type] " << getType() << std::endl << getOriginString();
  m_WhatBuffer = oss.str();
  return m_WhatBuffer.c_str();
}

const char *Destiny::Exception::getType() const { return "Destiny Exception"; }

uint16_t Destiny::Exception::getLine() const { return m_Line; }

const std::string &Destiny::Exception::getFile() const { return m_File; }

const std::string &Destiny::Exception::getMsg() const { return m_Msg; }

std::string Destiny::Exception::getOriginString() const {
  std::ostringstream oss;
  oss << "[File] " << m_File << std::endl
      << "[Line] " << m_Line << std::endl
      << "[Message] " << m_Msg;
  return oss.str();
}
