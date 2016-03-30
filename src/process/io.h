#pragma once

#include <cstdint>
#include <unistd.h>

namespace traitorous {

void Print(const String& string) noexcept {
  write(1, string.CString(), string.Capacity());
}

void PrintLn(const String& string) noexcept {
  write(1, string.CString(), string.Capacity());
  write(1, "\n", 1);
}

}
