#pragma once

#include <everest/memory/mutable_memory.h>
#include <everest/memory/mutable/container.h>

namespace everest {

template <class T>
class MutableMemory;

template <class T>
class Container<MutableMemory<T>> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableMemory<T>& memory) noexcept {
    return memory.Length();
  }

  static bool IsEmpty(const MutableMemory<T>& memory) noexcept {
    return memory.IsEmpty();
  }

};


}