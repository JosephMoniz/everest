#pragma once

#include <everest/containers/mutable/mutable_bit_set.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class MutableBitSet;

template <>
class Copyable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static MutableBitSet Copy(const MutableBitSet& bitSet) noexcept {
    return bitSet.Copy();
  }

};

}