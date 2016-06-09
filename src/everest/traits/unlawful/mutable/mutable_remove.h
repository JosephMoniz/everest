#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableRemove {

  typedef MutableRemove<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class U>
  static F& RemoveInPlace(const U& item, F& container) noexcept {
    return Base::RemoveInPlace(item, container);
  }

  template <class F>
  static F& RemoveInPlace(const F& source, F& container) noexcept {
    return Base::RemoveInPlace(source, container);
  }

};

template <class F, class T>
F& RemoveInPlace(const T& item, F& container) noexcept {
  return MutableRemove<F>::RemoveInPlace(item, container);
}

template <class F>
F& RemoveInPlace(const F& source, F& container) noexcept {
  return MutableRemove<F>::RemoveInPlace(source, container);
}

}

#pragma clang diagnostic pop