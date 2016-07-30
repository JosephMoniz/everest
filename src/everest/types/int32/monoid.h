#pragma once

#include <everest/types/int32.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class Int32;

template <>
class Monoid<Int32> final {
public:

  static constexpr bool exists = true;

};

}