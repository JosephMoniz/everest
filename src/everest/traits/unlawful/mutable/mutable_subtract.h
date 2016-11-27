#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <utility>

namespace everest {

template <class T>
class MutableSubtract {

  typedef MutableSubtract<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class U>
  static F& SubtractInPlace(const U& item, F& container) noexcept {
    return Base::SubtractInPlace(item, container);
  }

  template <class F, class U>
  static F& SubtractInPlace(U&& item, F& container) noexcept {
    return Base::SubtractInPlace(std::move(item), container);
  }

  template <class F>
  static F& SubtractInPlace(const F& source, F& container) noexcept {
    return Base::SubtractInPlace(source, container);
  }

  template <class F>
  static F& SubtractInPlace(F&& source, F& container) noexcept {
    return Base::SubtractInPlace(std::move(source), container);
  }

};

template <class F, class T>
F& SubtractInPlace(const T& item, F& container) noexcept {
  static_assert(MutableSubtract<F>::exists, "F does not implement MutableSubtract");
  return MutableSubtract<F>::SubtractInPlace(item, container);
}

template <class F, class T>
F& SubtractInPlace(T&& item, F& container) noexcept {
  static_assert(MutableSubtract<F>::exists, "F does not implement MutableSubtract");
  return MutableSubtract<F>::SubtractInPlace(std::move(item), container);
}

template <class F>
F& SubtractInPlace(const F& source, F& container) noexcept {
  static_assert(MutableSubtract<F>::exists, "F does not implement MutableSubtract");
  return MutableSubtract<F>::SubtractInPlace(source, container);
}

template <class F>
F& SubtractInPlace(F&& source, F& container) noexcept {
  static_assert(MutableSubtract<F>::exists, "F does not implement MutableSubtract");
  return MutableSubtract<F>::SubtractInPlace(std::move(source), container);
}

}

#pragma clang diagnostic pop