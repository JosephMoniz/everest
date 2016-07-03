#pragma once

#include <initializer_list>
#include <everest/memory/shared.h>
#include <everest/traits/lawful/functor.h>
#include <everest/traits/unlawful/pointable.h>

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

#include "everest/containers/array/pointable.h"
#include "everest/containers/array/shows.h"
#include "everest/containers/array/eq.h"
#include "everest/containers/array/ord.h"
#include "everest/containers/array/functor.h"
#include "everest/containers/array/containable.h"
#include "everest/containers/array/container.h"
#include "everest/containers/array/semigroup.h"
#include "everest/containers/array/zero.h"
#include "everest/containers/array/monoid.h"
#include "everest/containers/array/hashable.h"
#include "everest/containers/array/foldable.h"