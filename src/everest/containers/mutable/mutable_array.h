#pragma once

#include <initializer_list>
#include <everest/traits/lawful/functor.h>
#include <everest/traits/unlawful/mutable/mutable_add.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class T, size_t S>
class MutableArray final {

  friend class Functor<MutableArray<T, S>>;
  friend class Iteration<MutableArray<T, S>>;

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
    for (size_t i = 0; i < length; i++) {
      _array[i] = pointer[i];
    }
  }

  const T* Pointer() const noexcept {
    return (const T*) &_array;
  };

  T* MutablePointer() const noexcept {
    return (T*) &_array;
  };

};

template <class T, size_t S>
class Iteration<MutableArray<T, S>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableArray<T, S>& container, const F& function) noexcept {
    for (auto i = 0; i < S; i++) {
      function(container._array[i]);
    }
  }

};

}

#include <everest/containers/mutable/array/shows.h>
#include <everest/containers/mutable/array/eq.h>
#include <everest/containers/mutable/array/ord.h>
#include <everest/containers/mutable/array/functor.h>
#include <everest/containers/mutable/array/containable.h>
#include <everest/containers/mutable/array/container.h>
#include <everest/containers/mutable/array/semigroup.h>
#include <everest/containers/mutable/array/zero.h>
#include <everest/containers/mutable/array/monoid.h>
#include <everest/containers/mutable/array/hashable.h>
#include <everest/containers/mutable/array/foldable.h>