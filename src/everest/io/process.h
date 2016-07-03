#pragma once

#include <unistd.h>
#include <everest/types/string.h>

namespace everest {

void Print(const String& string) noexcept {
  write(1, Pointer(string), Occupied(string));
}

void PrintLn(const String& string) noexcept {
  write(1, Pointer(string), Occupied(string));
  write(1, "\n", 1);
}

}