#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Disjoinable {

  typedef Disjoinable<T> Base;

public:

  static constexpr bool exists = false;

  template <class T>
  static T Disjoin(const T& a, const T& b) noexcept {
    return Base::Disjoin(a, b);
  }

};

template <class T>
T Disjoin(const T& a, const T& b) noexcept {
  static_assert(Disjoinable<T>::exists, "T does not implement Disjoinable");
  return Disjoinable<T>::Disjoin(a, b);
}

}

#pragma clang diagnostic pop