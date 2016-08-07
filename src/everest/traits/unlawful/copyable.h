#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


#include <stddef.h>

namespace everest {

template <class T>
class Copyable {

  typedef Copyable<T> Base;

public:

  static constexpr bool exists = false;

  static T Copy(const T& n) {
    return Base::Copy(n);
  }

};

template<class T>
T Copy(const T& n) noexcept {
  static_assert(Copyable<T>::exists, "T does not implement Copyable");
  return Copyable<T>::Copy(n);
}

}

#pragma clang diagnostic pop