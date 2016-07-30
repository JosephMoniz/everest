#pragma once

#include <everest/types/int16.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class Int16;

template <>
class Monoid<Int16> final {
public:

  static constexpr bool exists = true;

};

}