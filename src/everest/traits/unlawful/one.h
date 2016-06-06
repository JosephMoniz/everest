#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class OneVal {

  typedef OneVal<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static constexpr U One() noexcept {
    return Base::One();
  }

};

template <class T>
constexpr T One() noexcept {
  return OneVal<T>::One();
}

}

#pragma clang diagnostic pop