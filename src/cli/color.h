#ifndef TRAITOROUS_COLOR_H
#define TRAITOROUS_COLOR_H

#include <string>

namespace traitorous {

std::string Black(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;30") + str + std::string("\033[0m");
}

std::string DarkGray(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;30") + str + std::string("\033[0m");
}

std::string Blue(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;34m") + str + std::string("\033[0m");
}

std::string LightBlue(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;34m") + str + std::string("\033[0m");
}

std::string Green(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;32m") + str + std::string("\033[0m");
}

std::string LightGreen(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;32m") + str + std::string("\033[0m");
}

std::string Cyan(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;36m") + str + std::string("\033[0m");
}

std::string LightCyan(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;36m") + str + std::string("\033[0m");
}

std::string Red(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;31m") + str + std::string("\033[0m");
}

std::string LightRed(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;31m") + str + std::string("\033[0m");
}

std::string Purple(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;35m") + str + std::string("\033[0m");
}

std::string LightPurple(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;35m") + str + std::string("\033[0m");
}

std::string Brown(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;33m") + str + std::string("\033[0m");
}

std::string Yellow(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;33m") + str + std::string("\033[0m");
}

std::string LightGray(const std::string &str) noexcept {
  return std::string("\033[") + std::string("0;37m") + str + std::string("\033[0m");
}

std::string White(const std::string &str) noexcept {
  return std::string("\033[") + std::string("1;37m") + str + std::string("\033[0m");
}

std::string BgBlack(const std::string &str) noexcept {
  return std::string("\033[") + std::string("40m") + str + std::string("\033[0m");
}

std::string BgRed(const std::string &str) noexcept {
  return std::string("\033[") + std::string("41m") + str + std::string("\033[0m");
}

std::string BgGreen(const std::string &str) noexcept {
  return std::string("\033[") + std::string("42m") + str + std::string("\033[0m");
}

std::string BgYellow(const std::string &str) noexcept {
  return std::string("\033[") + std::string("43m") + str + std::string("\033[0m");
}

std::string BgBlue(const std::string &str) noexcept {
  return std::string("\033[") + std::string("44m") + str + std::string("\033[0m");
}

std::string BgMagenta(const std::string &str) noexcept {
  return std::string("\033[") + std::string("45m") + str + std::string("\033[0m");
}

std::string BgCyan(const std::string &str) noexcept {
  return std::string("\033[") + std::string("46m") + str + std::string("\033[0m");
}

std::string BgLightGray(const std::string &str) noexcept {
  return std::string("\033[") + std::string("47m") + str + std::string("\033[0m");
}

}

#endif
