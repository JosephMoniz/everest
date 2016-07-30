#pragma once

#include <everest/types/int64.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class Int64;

template <>
class Monoid<Int64> final {
public:

  static constexpr bool exists = true;

};

}