#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class UInt64;

template<>
class Fundamental<UInt64> final {
public:

  static constexpr bool exists = true;

};

}