#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


#include <stddef.h>

namespace everest {

template <class T>
class Container {

  typedef Container<T> Base;

public:

  static constexpr size_t Length(const T& n) {
    return Base::Length(n);
  }

  static constexpr bool IsEmpty(const T& n) {
    return Base::IsEmpty(n);
  }

  static constexpr bool exists = false;
};

template<class T>
constexpr inline size_t Length(const T& n) noexcept {
  return Container<T>::Length(n);
}

template<class T>
constexpr inline bool IsEmpty(const T& n) noexcept {
  return Container<T>::IsEmpty(n);
}

}

#pragma clang diagnostic pop