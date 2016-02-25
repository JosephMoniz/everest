#ifndef TRAITOROUS_CONTAINERS_ARRAY_EQ_H
#define TRAITOROUS_CONTAINERS_ARRAY_EQ_H

#include "containers/array.h"
#include "traits/unlawful/eq.h"

namespace traitorous {

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template<class T, size_t S>
class Eq<Array<T, S>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Array<T, S>& lhs, const Array<T, S>& rhs) noexcept {
    return Eq<LocalArray<T, S>>::Equals(*lhs.Pointer(), *rhs.Pointer());
  }

  template<size_t Rs>
  static bool Equals(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return false;
  }

};

}

#endif
