#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableRemove {

  typedef MutableRemove<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T& RemoveInPlace(const U& item, T& container) noexcept {
    static_assert(exists, "T does not implement MutableRemove");
    return Base::RemoveInPlace(item, container);
  }

  static T& RemoveInPlace(const T& source, T& container) noexcept {
    static_assert(exists, "T does not implement MutableRemove");
    return Base::RemoveInPlace(source, container);
  }

};

template <class F, class T>
F& RemoveInPlace(const T& item, F& container) noexcept {
  static_assert(MutableRemove<F>::exists, "F does not implement MutableRemove");
  return MutableRemove<F>::RemoveInPlace(item, container);
}

template <class F>
F& RemoveInPlace(const F& source, F& container) noexcept {
  static_assert(MutableRemove<F>::exists, "F does not implement MutableRemove");
  return MutableRemove<F>::RemoveInPlace(source, container);
}

}

#pragma clang diagnostic pop