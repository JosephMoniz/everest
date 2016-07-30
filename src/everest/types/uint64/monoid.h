#pragma once

#include <everest/types/uint64.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class UInt64;

template <>
class Monoid<UInt64> final {
public:

  static constexpr bool exists = true;

};

}