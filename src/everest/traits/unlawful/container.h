#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


#include <stddef.h>
#include <everest/types/size.h>
#include <everest/types/bool.h>

namespace everest {

template <class T>
class Container {

  typedef Container<T> Base;

public:

  static constexpr bool exists = false;

  static size_t Length(const T& n) {
    return Base::Length(n);
  }

  static bool IsEmpty(const T& n) {
    return Base::IsEmpty(n);
  }

};

template<class T>
size_t Length(const T& n) noexcept {
  return Container<T>::Length(n);
}

template<class T>
bool IsEmpty(const T& n) noexcept {
  return Container<T>::IsEmpty(n);
}

}

#pragma clang diagnostic pop