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
    static_assert(exists, "T does not implement Container");
    return Base::Length(n);
  }

  static bool IsEmpty(const T& n) {
    static_assert(exists, "T does not implement Container");
    return Base::IsEmpty(n);
  }

};

template<class T>
size_t Length(const T& n) noexcept {
  static_assert(Container<T>::exists, "T does not implement Container");
  return Container<T>::Length(n);
}

template<class T>
bool IsEmpty(const T& n) noexcept {
  static_assert(Container<T>::exists, "T does not implement Container");
  return Container<T>::IsEmpty(n);
}

}

#pragma clang diagnostic pop