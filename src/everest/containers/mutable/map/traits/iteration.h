#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

template<class K, class V>
class MutableMap;


template <class K, class V>
class Iteration<MutableMap<K, V>> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableMap<K, V>& container, const F& function) noexcept {
    auto memorySize    = container._memory.Length();
    auto memoryPointer = container._memory.Pointer();
    for (size_t i = 0; i < memorySize; i++) {
      memoryPointer[i].ForEach([&](const MutableMapEntry<K, V>& entry) {
        function(entry);
      });
    }
  }

};

}