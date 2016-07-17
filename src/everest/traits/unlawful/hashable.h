#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <cstddef>
#include <everest/types/expressive/hash_value.h>

namespace everest {

template <class T>
class Hashable {

  typedef Hashable<T> Base;

public:

  static constexpr bool exists = false;

  static HashValue Hash(const T& n) noexcept {
    return Base::Hash(n);
  }

};

template <class T>
class DefaultHashable {
public:

  static constexpr bool exists = true;

  static HashValue Hash(const T& hashable) noexcept {
    return HashValue((unsigned int) hashable);
  }

};

template <class T>
HashValue Hash(const T& hashable) noexcept {
  return Hashable<T>::Hash(hashable);
}

template <class T>
HashValue SeededHash(unsigned int seed, const T& hashable) noexcept {
  return HashValue(37 * seed + Hashable<T>::Hash(hashable).Value());
}

HashValue MultiHash(size_t count, HashValue hash) noexcept {
  auto mask  = ~0;
  auto shift = sizeof(int) * 4;
  auto upper = hash.Value() & (mask << shift);
  auto lower = hash.Value() & (mask >> shift);
  return (unsigned int) (upper + count * lower);
}

template <class T>
HashValue MultiHash(size_t count, const T& hashable) noexcept {
  return MultiHash(count, Hashable<T>::Hash(hashable));
}

}

#pragma clang diagnostic pop
