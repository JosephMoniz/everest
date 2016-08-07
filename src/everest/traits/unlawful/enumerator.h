#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


#include <everest/containers/option.h>

namespace everest {

template<class T>
class Enumerator {

  typedef Enumerator<T> Base;

public:

  static constexpr bool exists = false;

  static const Option<T> Next(const T& enumerator) {
    return Base::Next(enumerator);
  }

};

template<class T>
static const Option<T> Next(const T& enumerator) noexcept {
  static_assert(Enumerator<T>::exists, "T does not implement Enumerator");
  return Enumerator<T>::Next(enumerator);
};

}

#pragma clang diagnostic pop
