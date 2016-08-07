#pragma once

#include <everest/mutable_containers/mutable_bit_set.h>
#include <everest/traits/unlawful/iteration.h>

namespace everest {

class MutableBitSet;

template <>
class Iteration<MutableBitSet> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const MutableBitSet& bitSet, F function) noexcept {
    bitSet.ForEach(function);
  }

};

}