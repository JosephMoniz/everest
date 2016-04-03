#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

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

#pragma clang diagnostic pop
