#pragma once

#include <utility>

namespace everest {

template <class T>
class MutableInsert {

  typedef MutableInsert<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static T& InsertInPlace(const U& item, size_t position, T& container) noexcept {
    return Base::InsertInPlace(item, position, container);
  }

  template <class U>
  static T& InsertInPlace(U&& item, size_t position, T& container) noexcept {
    return Base::InsertInPlace(std::move(item), position, container);
  }

};

template <class T, class U>
T& InsertInPlace(const U& item, size_t position, T& container) noexcept {
  static_assert(MutableInsert<T>::exists, "T does not implement MutableInsert");
  return MutableInsert<T>::InsertInPlace(item, position, container);
};

template <class T, class U>
T& InsertInPlace(U&& item, size_t position, T& stack) noexcept {
  static_assert(MutableInsert<T>::exists, "T does not implement MutableInsert");
  return MutableInsert<T>::InsertInPlace(std::move(item), position, stack);
};

}