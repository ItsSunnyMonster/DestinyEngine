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
