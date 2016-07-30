#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class UInt8;

template<>
class Fundamental<UInt8> final {
public:

  static constexpr bool exists = true;

};

}