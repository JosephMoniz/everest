#pragma once

#include <everest/containers/mutable/mutable_map.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

template<class K, class V>
class MutableMap;

template<class K, class V>
class Eq<MutableMap<K, V>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableMap<K, V>& lhs, const MutableMap<K, V>& rhs) noexcept {
    if (Length(lhs) == Length(rhs)) {
      auto length  = Length(lhs._memory);
      auto pointer = Pointer(lhs._memory);
      for (auto i = 0; i < length; i ++) {
        auto mismatch = Any([&](MutableMapEntry<K, V>& entry) {
          auto matched = GetInPlace(entry.Key(), rhs);
          return matched == nullptr || *matched == entry.Value();
        }, pointer[i]);
        if (mismatch) {
          return false;
        }
      }
      return true;
    } else {
      return false;
    }
  }

};

}