#pragma once

#include <everest/types/int64.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Int64;

template<>
class Fundamental<Int64> final {
public:

  static constexpr bool exists = true;

};

}