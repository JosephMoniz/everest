#pragma once

#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class MutableAdd {

  typedef MutableAdd<T> Base;

public:

  static constexpr bool exists = false;

  template <class F, class U>
  static F& AddInPlace(const U& item, F& container) noexcept {
    return Base::AddInPlace(item, container);
  }

  template <class F, class U>
  static F& AddInPlace(U&& item, F& container) noexcept {
    return Base::AddInPlace(std::move(item), container);
  }

  template <class F>
  static F& AddInPlace(const F& source, F& container) noexcept {
    return Base::AddInPlace(source, container);
  }

  template <class F>
  static F& AddInPlace(F&& source, F& container) noexcept {
    return Base::AddInPlace(std::move(source), container);
  }

};

template <class F, class T>
F& AddInPlace(const T& item, F& container) noexcept {
  return MutableAdd<F>::AddInPlace(item, container);
}

template <class F, class T>
F& AddInPlace(T&& item, F& container) noexcept {
  return MutableAdd<F>::AddInPlace(std::move(item), container);
}

template <class F>
F& AddInPlace(const F& source, F& container) noexcept {
  return MutableAdd<F>::AddInPlace(source, container);
}

template <class F>
F& AddInPlace(F&& source, F& container) noexcept {
  return MutableAdd<F>::AddInPlace(std::move(source), container);
}

}

#pragma clang diagnostic pop