#pragma once

#include <utility>
#include <everest/memory/shared/shared_container.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

template<class T>
class Shared final {

  friend class Pointable<Shared<T>>;

  SharedContainer<T>* _container;

public:

  Shared() noexcept : _container(nullptr) { }

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
    bool wasSet = false;
    SharedContainer<T>* tmp = _container;
    if (_container != nullptr) {
      wasSet = true;
    }
    _container = other._container;
    if (_container != nullptr) {
      _container->Ref();
    }
    if (wasSet) {
      tmp->UnRef();
    }
    return *this;
  }

  Shared& operator=(Shared<T>&& other) noexcept {
    bool wasSet = false;
    SharedContainer<T>* tmp = _container;
    if (_container != nullptr) {
      wasSet = true;
    }
    _container       = other._container;
    other._container = nullptr;
    if (wasSet) {
      tmp->UnRef();
    }
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

};

template<class T, class ...As>
Shared<T> MakeShared(As&&... args) {
  return Shared<T>(new SharedContainer<T>(std::forward<As>(args)...));
}

template <class T>
class Pointable<Shared<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Shared<T>& memory) noexcept {
    return memory._container != nullptr
      ? memory._container->Data()
      : nullptr;
  }

};

}
