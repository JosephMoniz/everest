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

  Shared(const Shared<T>& other) : _count(other._count), _pointer(other._pointer) {
    (*_count)++;
  }

  ~Shared() {
    if (--(*_count) == 0) {
      delete _pointer;
      delete _count;
    }
  }

  T *operator->() const {
    return _pointer;
  }

  T &operator*() const {
    return *_pointer;
  }

};

template<class T, class ...As>
Shared<T> MakeShared(As&&... args) {
  return Shared<T>(new T(args...));
}

}

#endif
