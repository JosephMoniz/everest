#ifndef TRAITOROUS_COLOR_H
#define TRAITOROUS_COLOR_H

#include <string>

namespace traitorous {

std::string black(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;30") + str + std::string("\033[0m");
}

std::string dark_gray(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;30") + str + std::string("\033[0m");
}

std::string blue(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;34m") + str + std::string("\033[0m");
}

std::string light_blue(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;34m") + str + std::string("\033[0m");
}

std::string green(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;32m") + str + std::string("\033[0m");
}

std::string light_green(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;32m") + str + std::string("\033[0m");
}

std::string cyan(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;36m") + str + std::string("\033[0m");
}

std::string light_cyan(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;36m") + str + std::string("\033[0m");
}

std::string red(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;31m") + str + std::string("\033[0m");
}

std::string light_red(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;31m") + str + std::string("\033[0m");
}

std::string purple(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;35m") + str + std::string("\033[0m");
}

std::string light_purple(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;35m") + str + std::string("\033[0m");
}

std::string brown(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;33m") + str + std::string("\033[0m");
}

std::string yellow(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;33m") + str + std::string("\033[0m");
}

std::string light_gray(const std::string& str) noexcept {
  return std::string("\033[") + std::string("0;37m") + str + std::string("\033[0m");
}

std::string white(const std::string& str) noexcept {
  return std::string("\033[") + std::string("1;37m") + str + std::string("\033[0m");
}

std::string bg_black(const std::string& str) noexcept {
  return std::string("\033[") + std::string("40m") + str + std::string("\033[0m");
}

std::string bg_red(const std::string& str) noexcept {
  return std::string("\033[") + std::string("41m") + str + std::string("\033[0m");
}

std::string bg_green(const std::string& str) noexcept {
  return std::string("\033[") + std::string("42m") + str + std::string("\033[0m");
}

std::string bg_yellow(const std::string& str) noexcept {
  return std::string("\033[") + std::string("43m") + str + std::string("\033[0m");
}

std::string bg_blue(const std::string& str) noexcept {
  return std::string("\033[") + std::string("44m") + str + std::string("\033[0m");
}

std::string bg_magenta(const std::string& str) noexcept {
  return std::string("\033[") + std::string("45m") + str + std::string("\033[0m");
}

std::string bg_cyan(const std::string& str) noexcept {
  return std::string("\033[") + std::string("46m") + str + std::string("\033[0m");
}

std::string bg_light_gray(const std::string& str) noexcept {
  return std::string("\033[") + std::string("47m") + str + std::string("\033[0m");
}

}

#endif
