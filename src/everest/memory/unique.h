#pragma once

#include <utility>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T>
class Unique {

  friend class Pointable<Unique<T>>;

  T* _pointer;

public:

  Unique(T* container) noexcept : _pointer(_pointer) { }

  Unique(const Unique<T>& other) noexcept {
    _pointer = new T(&other._pointer);
  }

  Unique(Unique<T>&& other) noexcept : _pointer(std::move(other._pointer)) {
    other._pointer = nullptr;
  }

  ~Unique() {
    if (_pointer != nullptr) {
      delete _pointer;
    }
  }

  T* operator->() const noexcept {
    return _pointer;
  }

  T& operator*() const noexcept {
    return *_pointer;
  }

};

template<class T, class ...As>
Unique<T> MakeUnique(const As&... args) {
  return Unique<T>(new T(args...));
}

 template <class T>
class Pointable<Unique<T>> {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Unique<T>& memory) noexcept {
    return memory._pointer;
  }

};

}
