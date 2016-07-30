#pragma once

#include <everest/memory/memory.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

class Memory;

template <class T>
class Container<Memory<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const Memory<T>& memory) noexcept {
    return memory.Length();
  }

  static bool IsEmpty(const Memory<T>& memory) noexcept {
    return memory.IsEmpty();
  }

};

}