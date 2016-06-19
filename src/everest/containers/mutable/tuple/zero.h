#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/unlawful/zero.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class ZeroVal<MutableTuple<T, U>> {
public:

  static constexpr bool exists = true;

  static MutableTuple<T, U> Zero() noexcept {
    return MutableTuple<T, U>(ZeroVal<T>::Zero(), ZeroVal<U>::Zero());
  }

};

}