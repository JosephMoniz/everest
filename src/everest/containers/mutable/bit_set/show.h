#pragma once

#include <everest/containers/mutable/mutable_bit_set.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class MutableBitSet;

template <>
class Shows<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableBitSet& bitSet) noexcept {
    return bitSet.Show();
  }

};

}