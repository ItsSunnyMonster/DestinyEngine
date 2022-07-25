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
