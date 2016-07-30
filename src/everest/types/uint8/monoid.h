#pragma once

#include <everest/types/uint8.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class UInt8;

template <>
class Monoid<UInt8> final {
public:

  static constexpr bool exists = true;

};

}