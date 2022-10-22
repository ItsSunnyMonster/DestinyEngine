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

#include <dtpch.hpp>

namespace Destiny {

class Exception : public std::exception {
public:
  Exception(uint64_t line, const char *file);
  Exception(uint64_t line, const char *file, const char *msg);
  char const *what() const noexcept override;
  virtual const char *getType() const;
  uint64_t getLine() const;
  const std::string &getFile() const;
  const std::string &getMsg() const;
  std::string getOriginString() const;

private:
  uint64_t m_Line;
  std::string m_File;
  std::string m_Msg;

protected:
  mutable std::string m_WhatBuffer;
};

} // namespace Destiny
