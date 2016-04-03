#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/types/string.h>

namespace everest {

template <class T>
class Shows {

  typedef Shows<T> Base;

public:

  static constexpr bool exists = false;

  static String Show(const T& n) noexcept {
    return Base::Show(n);
  }

};

template <class T>
const String Show(const T& n) noexcept {
  return Shows<T>::Show(n);
}

}

#pragma clang diagnostic pop
