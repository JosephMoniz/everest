#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/memory/mutable/pointable.h>

namespace everest {

template <class T>
class MutableMemory;

template<class T>
class Pointable<MutableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const MutableMemory<T>& memory) noexcept {
    return memory.Pointer();
  }

};

}