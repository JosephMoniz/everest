#pragma once

#include <stddef.h>
#include <type_traits>

namespace everest {

template<class T>
class SharedContainer {

  using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;

  size_t _count;

  data_t _data;

public:

  template<class ...As>
  SharedContainer(const As&... args) noexcept : _count(1) {
    new (&_data) T(args...);
  }

  void Ref() noexcept {
    _count++;
  }

  size_t UnRef() noexcept {
    return --_count;
  }

  T* Data() const noexcept {
    return (T*) &_data;
  }

};

}