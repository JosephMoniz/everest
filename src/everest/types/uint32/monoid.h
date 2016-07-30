#pragma once

#include <everest/types/uint32.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class UInt32;

template <>
class Monoid<UInt32> final {
public:

  static constexpr bool exists = true;

};

}