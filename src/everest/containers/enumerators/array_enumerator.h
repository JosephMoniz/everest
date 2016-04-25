#pragma once

#include "mutable_array.h"
#include <everest/traits/unlawful/enumerator.h>
#include <everest/containers/option.h>

namespace everest {

template<class T>
class ArrayEnumerator {

  SharedArray<T> _array;

  size_t _position;

public:

  ArrayEnumerator(const SharedArray<T>& array) noexcept : _array(array), _position(0) {
    //
  }

  ArrayEnumerator(const ArrayEnumerator<T>& other) noexcept : _array(other._array),
                                                              _position(other._position)
  {
    //
  }

  ArrayEnumerator<T>& operator=(const ArrayEnumerator<T>& enumerator) noexcept {
    _array = enumerator._array;
    return *this;
  }

};

template<class T>
class Enumerator<ArrayEnumerator<T>> {
public:

  static constexpr bool exists = true;

  static constexpr Option<T> Next(const T& enumerator) noexcept {
    if (enumerator._position >= enumerator._array->Size()) {
      return Some(enumerator._array->pointer()[enumerator._position++]);
    } else {
      return None<T>();
    }
  }

};

}
