#pragma once

#include <everest/types/int8.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class Int8;

template <>
class Monoid<Int8> final {
public:

  static constexpr bool exists = true;

};

}