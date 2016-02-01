#ifndef TRAITOROUS_CONTAINERS_SHARED_H
#define TRAITOROUS_CONTAINERS_SHARED_H

#include "types/uint32.h"

namespace traitorous {

template<class T>
class Shared {
private:

  uint32_t *_count;
  T *_pointer;

public:

  Shared(T* external) : _pointer(external) {
    _count = new uint32_t;
    *_count = 1;
  }

  Shared(T* external, uint32_t* count) : _pointer(external), _count(count) {
    (*_count)++;
  }

  Shared(const Shared<T>& other) : _count(other._count), _pointer(other._pointer) {
    (*_count)++;
  }

  ~Shared() {
    if (--(*_count) == 0) {
      delete _pointer;
      delete _count;
    }
  }

  T* operator->() const {
    return _pointer;
  }

  T& operator*() const {
    return *_pointer;
  }

  T* pointer() const {
    return _pointer;
  }

  uint32_t* counter() const {
    return _count;
  }

};

template<class T, class ...As>
Shared<T> MakeShared(As&&... args) {
  return Shared<T>(new T(args...));
}

template<class T, class U>
Shared<U> DynamicSharedCast(const Shared<T>& shared) {
  U* internal = dynamic_cast<U*>(shared.pointer());
  return Shared<U>(internal, shared.counter());
};

}

#endif
