#ifndef TRAITOROUS_CONTAINERS_ARRAY_H
#define TRAITOROUS_CONTAINERS_ARRAY_H

#include <cstdint>
#include <initializer_list>

#include "functions/identity.h"

#include "containers/shared.h"

#include "traits/unlawful/show.h"

namespace traitorous {

template<class T, size_t S>
class LocalArray {

  T _array[S];

public:

  LocalArray() {
    //
  }

  LocalArray(std::initializer_list<T> list) {
    std::copy(list.begin(), list.end(), _array);
  }

  size_t Size() const {
    return S;
  }

  const T* pointer() const {
    return (const int*) &_array;
  };

  T* mut_pointer() const {
    return (int*) &_array;
  };

};

template<class T, size_t S>
using Array = Shared<LocalArray<T, S>>;

template<class T, size_t S>
Array<T, S> MakeArray(std::initializer_list<T> list) {
  return MakeShared<LocalArray<T, S>>(list);
}

template<class T, size_t S>
Array<T, S> MakeArray() {
  return MakeShared<LocalArray<T, S>>();
}

}

#include "containers/local_array/shows.h"
#include "containers/local_array/eq.h"
#include "containers/local_array/ord.h"
#include "containers/local_array/functor.h"
#include "containers/local_array/containable.h"
#include "containers/local_array/container.h"
#include "containers/local_array/semigroup.h"
#include "containers/local_array/zero.h"
#include "containers/local_array/monoid.h"
#include "containers/local_array/hashable.h"
#include "containers/local_array/foldable.h"

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

#endif
