#pragma once

#include <everest/types/int8.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Int8;

template<>
class Fundamental<Int8> final {
public:

  static constexpr bool exists = true;

};

}