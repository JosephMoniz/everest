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
  static U One() noexcept {
    static_assert(exists, "T does not implement OneVal");
    return Base::One();
  }

};

template <class T>
T One() noexcept {
  static_assert(OneVal<T>::exists, "T does not implement OneVal");
  return OneVal<T>::One();
}

}

#pragma clang diagnostic pop