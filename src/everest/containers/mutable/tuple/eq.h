#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Eq<MutableTuple<T, U>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableTuple<T, U>& lhs, const MutableTuple<T, U>& rhs) noexcept {
    return lhs._first == rhs._first && lhs._second == rhs._second;
  }

};

}