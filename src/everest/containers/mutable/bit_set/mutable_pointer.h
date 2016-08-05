#pragma once

#include <everest/containers/mutable/mutable_bit_set.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class MutableBitSet;

template <>
class MutablePointable<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static int* Pointer(MutableBitSet& bitSet) noexcept {
    return bitSet.MutablePointer();
  }

};

}