#pragma once

#include <everest/types/int32.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Int32;

template<>
class Fundamental<Int32> final {
public:

  static constexpr bool exists = true;

};

}