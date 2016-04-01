#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace traitorous {

template <class T>
class OneVal {

  typedef OneVal<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr inline U One() noexcept {
    return Base::One();
  }

};

template <class T>
constexpr inline T One() noexcept {
  return OneVal<T>::One();
}

}

#pragma clang diagnostic pop