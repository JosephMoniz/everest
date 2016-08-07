#pragma once

#include <everest/mutable_containers/mutable_bit_set.h>
#include <everest/traits/unlawful/Pointable.h>

namespace everest {

class MutableBitSet;

template <>
class Pointable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static const int* Pointer(const MutableBitSet& bitSet) noexcept {
    return bitSet.Pointer();
  }

};

}