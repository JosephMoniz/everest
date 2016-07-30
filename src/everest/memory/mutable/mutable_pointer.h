#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/memory/mutable/mutable_pointer.h>

namespace everest {

template <class T>
class MutableMemory;

template<class T>
class MutablePointable<MutableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static T* Pointer(MutableMemory<T>& memory) noexcept {
    return memory.MutablePointer();
  }

};

}