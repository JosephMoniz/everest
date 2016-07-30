#pragma once

#include <everest/types/int16.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Int16;

template<>
class Fundamental<Int16> final {
public:

  static constexpr bool exists = true;

};

}