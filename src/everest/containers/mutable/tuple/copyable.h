#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Copyable<MutableTuple<T, U>> final {
public:

  static constexpr bool exists = true;

  static MutableTuple<T, U> Copy(const MutableTuple<T, U>& tuple) noexcept {
    return MutableTuple<T, U>(Copyable<T>::Copy(tuple._first), Copyable<U>::Copy(tuple._second));
  }

};

}