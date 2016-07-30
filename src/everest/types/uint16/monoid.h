#pragma once

#include <everest/types/uint16.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class UInt16;

template <>
class Monoid<UInt16> final {
public:

  static constexpr bool exists = true;

};

}