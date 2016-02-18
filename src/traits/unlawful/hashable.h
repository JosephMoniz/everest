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

  static constexpr int Hash(const T& n) noexcept {
    return Base::Hash(n);
  }

};

template <class T>
class DefaultHashable {
public:

  static constexpr bool exists = true;

  static constexpr int Hash(const T& hashable) noexcept {
    return (int) hashable;
  }

};

template <class T>
constexpr int Hash(const T& hashable) noexcept {
  return Hashable<T>::Hash(hashable);
}

}

#endif

#pragma clang diagnostic pop
