#pragma once

#include <everest/containers/mutable/mutable_bit_set.h>
#include <everest/traits/unlawful/container.h>

namespace everest {

class MutableBitSet;

template <>
class Container<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static size_t Length(const MutableBitSet& bitSet) noexcept {
    return bitSet.Length();
  }

  static bool IsEmpty(const MutableBitSet& bitSet) noexcept {
    return bitSet.IsEmpty();
  }

};

}