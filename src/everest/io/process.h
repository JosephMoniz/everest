#pragma once

#include <unistd.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/storable.h>

namespace everest {

void Print(const char* string) noexcept {
  write(1, string, strlen(string));
}

template <class T>
void Print(const T& subject) noexcept {
  static_assert(Pointable<T>::exists, "pointable doesn't exist for T");
  static_assert(Storable<T>::exists, "Storable doesn't exist for T");
  auto occupied = Occupied(subject);
  if (occupied > 0) {
    write(1, Pointer(subject), Occupied(subject) - 1);
  }
}

void PrintLn(const char* string) noexcept {
  write(1, string, strlen(string));
  write(1, "\n", 1);
}

template <class T>
void PrintLn(const T& subject) noexcept {
  static_assert(Pointable<T>::exists, "pointable doesn't exist for T");
  static_assert(Storable<T>::exists, "Storable doesn't exist for T");
  auto occupied = Occupied(subject);
  if (occupied > 0) {
    write(1, Pointer(subject), Occupied(subject) - 1);
  }
  write(1, "\n", 1);
}

}