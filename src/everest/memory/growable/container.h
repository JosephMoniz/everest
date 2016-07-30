#pragma once

#include <everest/memory/growable_memory.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

template <class T>
class GrowableMemory;

template <class T>
class Container<GrowableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const GrowableMemory<T>& memory) noexcept {
    return memory.Length();
  }

  static bool IsEmpty(const GrowableMemory<T>& memory) noexcept {
    return memory.IsEmpty();
  }

};

}