#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace traitorous {

template <class T>
class Disjoinable {

  typedef Disjoinable<T> Base;

public:

  static constexpr bool exists = false;

  template <class T>
  static constexpr inline T Disjoin(const T& a, const T& b) noexcept {
    return Base::Disjoin(a, b);
  }

};

template <class T>
constexpr inline T Disjoin(const T& a, const T& b) noexcept {
  return Disjoinable<T>::Disjoin(a, b);
}

}

#pragma clang diagnostic pop