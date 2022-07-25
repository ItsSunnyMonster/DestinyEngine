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

namespace Destiny {

class Exception : public std::exception {
public:
  Exception(uint16_t line, const char *file);
  Exception(uint16_t line, const char *file, const char *msg);
  char const *what() const noexcept override;
  virtual const char *getType() const;
  uint16_t getLine() const;
  const std::string &getFile() const;
  const std::string &getMsg() const;
  std::string getOriginString() const;

private:
  uint16_t m_Line;
  std::string m_File;
  std::string m_Msg;

protected:
  mutable std::string m_WhatBuffer;
};

} // namespace Destiny
