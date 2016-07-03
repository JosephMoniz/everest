#pragma once

#include <cstddef>

namespace everest {

template <class T>
class Storable {

  typedef Storable<T> Base;

public:

  static constexpr bool exists = false;

  static constexpr size_t Capacity(const T& storage) {
    return Base::Capacity(storage);
  }

  static constexpr size_t Occupied(const T& storage) {
    return Base::Occupied(storage);
  }

};

template<class T>
constexpr size_t Capacity(const T& storage) noexcept {
  return Storable<T>::Capacity(storage);
}

template<class T>
constexpr size_t Occupied(const T& storage) noexcept {
  return Storable<T>::Occupied(storage);
}

}