#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_CONTAINABLE
#define TRAITOROUS_TRAITS_CONTAINABLE 1

#include "containers/local_option.h"

namespace traitorous {

template <class F, class T>
class Containable {

  typedef Containable<F, T> Base;

public:

  static constexpr bool exists = false;

  static constexpr bool Contains(const T& n, const F& f) {
    return Base::Contains(n, f);
  }

};

template<class F, class T>
inline bool Contains(const T& n, const F& f) {
  return Containable<F, T>::Contains(n, f);
}

}

#endif

#pragma clang diagnostic pop