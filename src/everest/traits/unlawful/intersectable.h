#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Intersectable {

  typedef Intersectable<T> Base;

public:

  static constexpr bool exists = false;

  template <class T>
  static constexpr inline T Intersect(const T& a, const T& b) noexcept {
    return Base::Intersect(a, b);
  }

};

template <class T>
constexpr inline T Intersect(const T& a, const T& b) noexcept {
  return Intersectable<T>::Intersect(a, b);
}

}

#pragma clang diagnostic pop