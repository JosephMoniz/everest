#pragma once

#include <cstdint>
#include <initializer_list>

#include "functions/identity.h"

#include "containers/shared.h"

#include "traits/unlawful/show.h"

namespace traitorous {

template<class T, size_t S>
class Array final {

  friend class Functor<Array<T, S>>;

  T _array[S];

public:

  Array() {
    //
  }

  Array(std::initializer_list<T> list) {
    size_t i = 0;
    auto it  = list.begin();
    for (; it != list.end(); it++, i++) {
      _array[i] = *it;
    }
  }

  size_t Size() const noexcept {
    return S;
  }

  const T* Pointer() const noexcept {
    return (const T*) &_array;
  };

  T* MutablePointer() const noexcept {
    return (T*) &_array;
  };

};

template<class T, size_t S>
using SharedArray = Shared<Array<T, S>>;

template<class T, size_t S>
SharedArray<T, S> MakeSharedArray(std::initializer_list<T> list) {
  return MakeShared<Array<T, S>>(list);
}

template<class T, size_t S>
SharedArray<T, S> MakeSharedArray() {
  return MakeShared<Array<T, S>>();
}

}

#include "containers/array/shows.h"
#include "containers/array/eq.h"
#include "containers/array/ord.h"
#include "containers/array/functor.h"
#include "containers/array/containable.h"
#include "containers/array/container.h"
#include "containers/array/semigroup.h"
#include "containers/array/zero.h"
#include "containers/array/monoid.h"
#include "containers/array/hashable.h"
#include "containers/array/foldable.h"

#include "containers/shared_array/shows.h"
#include "containers/shared_array/eq.h"
#include "containers/shared_array/ord.h"
#include "containers/shared_array/functor.h"
#include "containers/shared_array/containable.h"
#include "containers/shared_array/container.h"
#include "containers/shared_array/semigroup.h"
#include "containers/shared_array/zero.h"
#include "containers/shared_array/monoid.h"
#include "containers/shared_array/hashable.h"
#include "containers/shared_array/foldable.h"