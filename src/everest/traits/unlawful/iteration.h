#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Iteration {

  typedef Iteration<T> Base;

public:

  static constexpr bool exists = false;

  template <class F>
  static void ForEach(const T& container, const F& function) noexcept {
    return Base::ForEach(container, function);
  }

};

template <class T, class F>
void ForEach(const T& container, const F& function) noexcept {
  return Iteration<T>::ForEach(container, function);
}

}

#pragma clang diagnostic pop