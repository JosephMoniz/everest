#pragma once

#include <cstddef>

namespace everest {

template <class T>
class Storable {

  typedef Storable<T> Base;

public:

  static constexpr bool exists = false;

  static size_t Capacity(const T& storage) {
    return Base::Capacity(storage);
  }

  static size_t Occupied(const T& storage) {
    return Base::Occupied(storage);
  }

};

template<class T>
size_t Capacity(const T& storage) noexcept {
  static_assert(Storable<T>::exists, "T does not implement Storable");
  return Storable<T>::Capacity(storage);
}

template<class T>
size_t Occupied(const T& storage) noexcept {
  static_assert(Storable<T>::exists, "T does not implement Storable");
  return Storable<T>::Occupied(storage);
}

}