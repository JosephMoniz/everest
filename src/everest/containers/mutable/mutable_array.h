#pragma once

#include <initializer_list>
#include <everest/containers/shared.h>

namespace everest {

template<class T, size_t S>
class MutableArray final {

  friend class Functor<MutableArray<T, S>>;

  T _array[S];

public:

  MutableArray() { }

  MutableArray(std::initializer_list<T> list) {
    size_t i = 0;
    auto it  = list.begin();
    for (; it != list.end(); it++, i++) {
      _array[i] = *it;
    }
  }

  MutableArray(const T* pointer, size_t length) noexcept {
    for (auto i = 0; i < length; i++) {
      _array[i] = pointer[i];
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
using SharedArray = Shared<MutableArray<T, S>>;

template<class T, size_t S>
SharedArray<T, S> MakeSharedArray(std::initializer_list<T> list) {
  return MakeShared<MutableArray<T, S>>(list);
}

template<class T, size_t S>
SharedArray<T, S> MakeSharedArray() {
  return MakeShared<MutableArray<T, S>>();
}

}

#include "everest/containers/mutable/array/traits/shows.h"
#include "everest/containers/mutable/array/traits/eq.h"
#include "everest/containers/mutable/array/traits/ord.h"
#include "everest/containers/mutable/array/traits/functor.h"
#include "everest/containers/mutable/array/traits/containable.h"
#include "everest/containers/mutable/array/traits/container.h"
#include "everest/containers/mutable/array/traits/semigroup.h"
#include "everest/containers/mutable/array/traits/zero.h"
#include "everest/containers/mutable/array/traits/monoid.h"
#include "everest/containers/mutable/array/traits/hashable.h"
#include "everest/containers/mutable/array/traits/foldable.h"

#include "everest/containers/mutable/array/traits/shared/shows.h"
#include "everest/containers/mutable/array/traits/shared/eq.h"
#include "everest/containers/mutable/array/traits/shared/ord.h"
#include "everest/containers/mutable/array/traits/shared/functor.h"
#include "everest/containers/mutable/array/traits/shared/containable.h"
#include "everest/containers/mutable/array/traits/shared/container.h"
#include "everest/containers/mutable/array/traits/shared/semigroup.h"
#include "everest/containers/mutable/array/traits/shared/zero.h"
#include "everest/containers/mutable/array/traits/shared/monoid.h"
#include "everest/containers/mutable/array/traits/shared/hashable.h"
#include "everest/containers/mutable/array/traits/shared/foldable.h"