#ifndef TRAITOROUS_CONTAINERS_ENUMERATORS_ARRAY_ENUMERATOR_H_H
#define TRAITOROUS_CONTAINERS_ENUMERATORS_ARRAY_ENUMERATOR_H_H

#include <containers/array.h>
#include <exceptions/no_such_element_exception.h>

namespace traitorous {

template<class T>
class ArrayEnumerator {

  Array<T> _array;

  size_t _position;

public:

  ArrayEnumerator(const Array<T>& array) noexcept : _array(array), _position(0) {
    //
  }

  ArrayEnumerator(const ArrayEnumerator<T>& enumerator) noexcept : _array(enumerator._array),
                                                                   _position(enumerator._position)
  {
    //
  }

  ArrayEnumerator(const ArrayEnumerator<T>&& enumerator) noexcept : _array(std::move(enumerator._array)),
                                                                    _position(std::move(enumerator._position))
  {
    //
  }

  ArrayEnumerator<T>& operator=(const ArrayEnumerator<T>& enumerator) noexcept {
    _array = enumerator._array;
    return *this;
  }

  bool HasNext() const noexcept {
    return _position >= _array->Size();
  }

  const T& Next() {
    if (HasNext()) {
      return _array->pointer()[_position++];
    } else {
      throw NoSuchElementException();
    }
  }

};

}

#endif
