#pragma once

#include <everest/containers/mutable/mutable_tuple.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<class T, class U>
class MutableTuple;

template<class T, class U>
class Shows<MutableTuple<T, U>> final {
public:

  static constexpr bool exists = true;

  static const String Show(const MutableTuple<T, U>& tuple) noexcept {
    return String("MutableTuple(") +
           Shows<T>::Show(tuple._first) +
           String(", ") +
           Shows<U>::Show(tuple._second) +
           String(")");
  }

};

}