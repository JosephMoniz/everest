#pragma once

#include <unistd.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/storable.h>

namespace everest {

template <class T>
void Print(const T& subject) noexcept {
  static_assert(Pointable<T>::exists, "pointable doesn't exist for T");
  static_assert(Storable<T>::exists, "Storable doesn't exist for T");
  write(1, Pointer(subject), Occupied(subject));
}

template <class T>
void PrintLn(const T& subject) noexcept {
  static_assert(Pointable<T>::exists, "pointable doesn't exist for T");
  static_assert(Storable<T>::exists, "Storable doesn't exist for T");
  write(1, Pointer(subject), Occupied(subject));
  write(1, "\n", 1);
}

}