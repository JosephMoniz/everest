#pragma once

#include <everest/memory/growable_memory.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

template <class T>
class GrowableMemory;

template <class T>
class Pointable<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const GrowableMemory<T>& memory) noexcept {
    return memory.Pointer();
  }

};

}