#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableFind {

  typedef MutableFind<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class U>
  static U& FindInPlace(const U& item, F& container) noexcept {
    return Base::FindInPlace(item, container);
  }

};

template <class F, class T>
auto FindInPlace(const T& item, F& container) noexcept -> decltype(MutableFind<F>::FindInPlace(item, container)) {
  return MutableFind<F>::FindInPlace(item, container);
}

}

#pragma clang diagnostic pop