#pragma once

#include <everest/memory/memory.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Memory;

template <class T>
class Pointable<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static const T* Pointer(const Memory<T>& memory) noexcept {
    return memory.Pointer();
  }

};

}