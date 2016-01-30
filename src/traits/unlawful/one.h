#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_ONE
#define TRAITOROUS_TRAITS_ONE 1

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

#endif

#pragma clang diagnostic pop