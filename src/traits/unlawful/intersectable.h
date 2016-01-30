#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_INTERSECTABLE
#define TRAITOROUS_TRAITS_INTERSECTABLE 1

namespace traitorous {

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

#endif

#pragma clang diagnostic pop