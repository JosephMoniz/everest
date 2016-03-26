#ifndef TRAITOROUS_COLOR_H
#define TRAITOROUS_COLOR_H

#include <types/string.h>

namespace traitorous {

LocalString Black(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;30") + str + LocalString("\033[0m");
}

LocalString DarkGray(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;30") + str + LocalString("\033[0m");
}

LocalString Blue(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;34m") + str + LocalString("\033[0m");
}

LocalString LightBlue(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;34m") + str + LocalString("\033[0m");
}

LocalString Green(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;32m") + str + LocalString("\033[0m");
}

LocalString LightGreen(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;32m") + str + LocalString("\033[0m");
}

LocalString Cyan(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;36m") + str + LocalString("\033[0m");
}

LocalString LightCyan(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;36m") + str + LocalString("\033[0m");
}

LocalString Red(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;31m") + str + LocalString("\033[0m");
}

LocalString LightRed(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;31m") + str + LocalString("\033[0m");
}

LocalString Purple(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;35m") + str + LocalString("\033[0m");
}

LocalString LightPurple(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;35m") + str + LocalString("\033[0m");
}

LocalString Brown(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;33m") + str + LocalString("\033[0m");
}

LocalString Yellow(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;33m") + str + LocalString("\033[0m");
}

LocalString LightGray(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("0;37m") + str + LocalString("\033[0m");
}

LocalString White(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("1;37m") + str + LocalString("\033[0m");
}

LocalString BgBlack(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("40m") + str + LocalString("\033[0m");
}

LocalString BgRed(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("41m") + str + LocalString("\033[0m");
}

LocalString BgGreen(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("42m") + str + LocalString("\033[0m");
}

LocalString BgYellow(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("43m") + str + LocalString("\033[0m");
}

LocalString BgBlue(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("44m") + str + LocalString("\033[0m");
}

LocalString BgMagenta(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("45m") + str + LocalString("\033[0m");
}

LocalString BgCyan(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("46m") + str + LocalString("\033[0m");
}

LocalString BgLightGray(const LocalString& str) noexcept {
  return LocalString("\033[") + LocalString("47m") + str + LocalString("\033[0m");
}

}

#endif
