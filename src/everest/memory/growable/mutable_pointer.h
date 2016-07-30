#pragma once

#include <everest/memory/growable_memory.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

template <class T>
class GrowableMemory;

template<class T>
class MutablePointable<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static T* Pointer(GrowableMemory<T>& memory) noexcept {
    return memory.MutablePointer();
  }

};

}