#ifndef TRAITOROUS_CONTAINERS_ENUMERATORS_ARRAY_ENUMERATOR_H_H
#define TRAITOROUS_CONTAINERS_ENUMERATORS_ARRAY_ENUMERATOR_H_H

#include <containers/array.h>
#include <traits/unlawful/enumerator.h>

namespace traitorous {

template<class T>
class ArrayEnumerator {

  Array<T> _array;

  size_t _position;

public:

  ArrayEnumerator(const Array<T>& array) noexcept : _array(array), _position(0) {
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

  static const LocalOption<T> Next(const T& enumerator) noexcept {
    if (enumerator._position >= enumerator._array->Size()) {
      return LocalOption<T>(enumerator._array->pointer()[enumerator._position++]);
    } else {
      return LocalOption<T>();
    }
  }

};

}

#endif
