#pragma once

#include <everest/mutable_containers/mutable_array.h>
#include <everest/traits/lawful/semigroup.h>

namespace everest {

template <class T, size_t S>
class MutableArray;

template <class T, size_t S>
class Semigroup<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  template <size_t Rs, size_t Ns = S + Rs>
  static MutableArray<T, S + Rs> Add(const MutableArray<T, S>& lhs, const MutableArray<T, Rs>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

}
