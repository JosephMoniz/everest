#pragma once

#include <utility>
#include <everest/containers/shared/shared_container.h>

namespace everest {

template<class T>
class Shared final {

  SharedContainer<T>* _container;

public:

  Shared(SharedContainer<T>* container) noexcept : _container(container) { }

  Shared(const Shared<T>& other) noexcept : _container(other._container) {
    if (_container != nullptr) {
      _container->Ref();
    }
  }

  Shared(Shared<T>&& other) noexcept : _container(std::move(other._container)) {
    other._container = nullptr;
  }

  Shared& operator=(const Shared<T>& other) noexcept {
    _container = other._container;
    if (_container != nullptr) {
      _container->Ref();
    }
    return *this;
  }

  Shared& operator=(Shared<T>&& other) noexcept {
    _container       = other._container;
    other._container = nullptr;
    return *this;
  }

  ~Shared() noexcept {
    if (_container != nullptr && _container->UnRef() == 0) {
      delete _container;
    }
  }

  T* operator->() const noexcept {
    return _container != nullptr
      ? _container->Data()
      : nullptr;
  }

  T& operator*() const noexcept {
    return *_container->Data();
  }

  T* Pointer() const noexcept {
    return _container != nullptr
      ? _container->Data()
      : nullptr;
  }

};

template<class T, class ...As>
Shared<T> MakeShared(const As&... args) {
  return Shared<T>(new SharedContainer<T>(args...));
}

}
