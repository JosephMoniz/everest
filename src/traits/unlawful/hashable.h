#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_HASHABLE
#define TRAITOROUS_TRAITS_HASHABLE 1

namespace traitorous {

template <class T>
class Hashable {

  typedef Hashable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr int Hash(const T& n) {
    return Base::Hash(n);
  }

};

template <class T>
constexpr int Hash(const T& n) {
  return Hashable<T>::Hash(n);
}

}

#endif

#pragma clang diagnostic pop