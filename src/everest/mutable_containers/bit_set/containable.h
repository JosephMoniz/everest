#pragma once

#include <everest/mutable_containers/mutable_bit_set.h>
#include <everest/traits/unlawful/containable.h>

namespace everest {

class MutableBitSet;

template <>
class Containable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static bool Contains(bool bit, const MutableBitSet& bitSet) noexcept {
    return bitSet.Contains(bit);
  }

};

}