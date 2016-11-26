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
  static T Intersect(const T& a, const T& b) noexcept {
    static_assert(exists, "T does not implement Intersectable");
    return Base::Intersect(a, b);
  }

};

template <class T>
T Intersect(const T& a, const T& b) noexcept {
  static_assert(Intersectable<T>::exists, "T does not implement Intersectable");
  return Intersectable<T>::Intersect(a, b);
}

}

#pragma clang diagnostic pop