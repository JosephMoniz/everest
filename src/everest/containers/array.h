#pragma once

#include <initializer_list>
#include <everest/memory/shared.h>
#include <everest/traits/lawful/functor.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T, size_t S>
class Array final {

  friend class Pointable<Array<T, S>>;
  friend class Functor<Array<T, S>>;
  friend class Iteration<Array<T, S>>;

  T _array[S];

public:

  Array() noexcept { }

  Array(std::initializer_list<T> list) noexcept {
    size_t i = 0;
    auto it  = list.begin();
    for (; it != list.end(); it++, i++) {
      _array[i] = *it;
    }
  }

  Array(const T* pointer, size_t length) noexcept {
    for (auto i = 0; i < length; i++) {
      _array[i] = pointer[i];
    }
  }

  T* MutablePointerAnnoyingHack() const noexcept {
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
SharedArray<T, S> MakeSharedArray(const T* pointer, size_t length) {
  return MakeShared<Array<T, S>>(pointer, length);
}

template<class T, size_t S>
SharedArray<T, S> MakeSharedArray() {
  return MakeShared<Array<T, S>>();
}

template <class T, size_t S>
class Iteration<Array<T, S>> {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const Array<T, S>& container, const F& function) noexcept {
    for (auto i = 0; i < S; i++) {
      function(container._array[i]);
    }
  }

};

}

#include "everest/containers/array/traits/pointable.h"
#include "everest/containers/array/traits/shows.h"
#include "everest/containers/array/traits/eq.h"
#include "everest/containers/array/traits/ord.h"
#include "everest/containers/array/traits/functor.h"
#include "everest/containers/array/traits/containable.h"
#include "everest/containers/array/traits/container.h"
#include "everest/containers/array/traits/semigroup.h"
#include "everest/containers/array/traits/zero.h"
#include "everest/containers/array/traits/monoid.h"
#include "everest/containers/array/traits/hashable.h"
#include "everest/containers/array/traits/foldable.h"

#include "everest/containers/array/traits/shared/pointable.h"
#include "everest/containers/array/traits/shared/shows.h"
#include "everest/containers/array/traits/shared/eq.h"
#include "everest/containers/array/traits/shared/ord.h"
#include "everest/containers/array/traits/shared/functor.h"
#include "everest/containers/array/traits/shared/containable.h"
#include "everest/containers/array/traits/shared/container.h"
#include "everest/containers/array/traits/shared/semigroup.h"
#include "everest/containers/array/traits/shared/zero.h"
#include "everest/containers/array/traits/shared/monoid.h"
#include "everest/containers/array/traits/shared/hashable.h"
#include "everest/containers/array/traits/shared/foldable.h"