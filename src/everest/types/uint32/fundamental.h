#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class UInt32;

template<>
class Fundamental<UInt32> final {
public:

  static constexpr bool exists = true;

};

}