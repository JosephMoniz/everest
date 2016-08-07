#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <cstddef>

namespace everest {

template <class T>
class MutableRemoveAt {

  typedef MutableRemoveAt<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T& RemoveAtInPlace(size_t position, T& container) noexcept {
    return Base::RemoveAtInPlace(position, container);
  }

};

template <class F, class T>
F& RemoveAtInPlace(const T& item, F& container) noexcept {
  static_assert(MutableRemoveAt<F>::exists, "T does not implement MutableRemoveAt");
  return MutableRemoveAt<F>::RemoveAtInPlace(item, container);
}

}

#pragma clang diagnostic pop