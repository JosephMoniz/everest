#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class UInt16;

template<>
class Fundamental<UInt16> final {
public:

  static constexpr bool exists = true;

};

}