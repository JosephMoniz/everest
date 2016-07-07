#pragma once

#include <unistd.h>
#include <everest/types/string.h>

namespace everest {

void Print(const String& string) noexcept {
  write(1, Pointer(string), Occupied(string));
}

void Print(String&& string) noexcept {
  Print(static_cast<const String&>(string));
}

template <class T>
void Print(T&& object) noexcept {
  Print(Show(std::forward<T>(object)));
}

void PrintLn(const String& string) noexcept {
  write(1, Pointer(string), Occupied(string));
  write(1, "\n", 1);
}

void PrintLn(String&& string) noexcept {
  PrintLn(static_cast<const String&>(string));
}

template <class T>
void PrintLn(T&& string) noexcept {
  PrintLn(Show(string));
}

}