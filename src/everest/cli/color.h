#pragma once

#include <everest/types/string.h>

namespace everest {

String Black(const String & str) noexcept {
  return String("\033[0;30") + str + String("\033[0m");
}

String DarkGray(const String & str) noexcept {
  return String("\033[1;30") + str + String("\033[0m");
}

String Blue(const String & str) noexcept {
  return String("\033[0;34m") + str + String("\033[0m");
}

String LightBlue(const String & str) noexcept {
  return String("\033[1;34m") + str + String("\033[0m");
}

String Green(const String & str) noexcept {
  return String("\033[0;32m") + str + String("\033[0m");
}

String LightGreen(const String & str) noexcept {
  return String("\033[1;32m") + str + String("\033[0m");
}

String Cyan(const String & str) noexcept {
  return String("\033[0;36m") + str + String("\033[0m");
}

String LightCyan(const String & str) noexcept {
  return String("\033[1;36m") + str + String("\033[0m");
}

String Red(const String & str) noexcept {
  return String("\033[0;31m") + str + String("\033[0m");
}

String LightRed(const String & str) noexcept {
  return String("\033[1;31m") + str + String("\033[0m");
}

String Purple(const String & str) noexcept {
  return String("\033[0;35m") + str + String("\033[0m");
}

String LightPurple(const String & str) noexcept {
  return String("\033[1;35m") + str + String("\033[0m");
}

String Brown(const String & str) noexcept {
  return String("\033[0;33m") + str + String("\033[0m");
}

String Yellow(const String & str) noexcept {
  return String("\033[1;33m") + str + String("\033[0m");
}

String LightGray(const String & str) noexcept {
  return String("\033[0;37m") + str + String("\033[0m");
}

String White(const String & str) noexcept {
  return String("\033[1;37m") + str + String("\033[0m");
}

String BgBlack(const String & str) noexcept {
  return String("\033[40m") + str + String("\033[0m");
}

String BgRed(const String & str) noexcept {
  return String("\033[41m") + str + String("\033[0m");
}

String BgGreen(const String & str) noexcept {
  return String("\033[42m") + str + String("\033[0m");
}

String BgYellow(const String & str) noexcept {
  return String("\033[43m") + str + String("\033[0m");
}

String BgBlue(const String & str) noexcept {
  return String("\033[44m") + str + String("\033[0m");
}

String BgMagenta(const String & str) noexcept {
  return String("\033[45m") + str + String("\033[0m");
}

String BgCyan(const String & str) noexcept {
  return String("\033[46m") + str + String("\033[0m");
}

String BgLightGray(const String & str) noexcept {
  return String("\033[47m") + str + String("\033[0m");
}

}