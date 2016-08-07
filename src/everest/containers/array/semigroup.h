#pragma once

#include <everest/containers/array.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T, size_t S>
class Array;

template <class T, size_t S>
class Semigroup<Array<T, S>> final {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static Array<T, S + Rs> Add(const Array<T, S>& lhs, const Array<T, Rs>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}
