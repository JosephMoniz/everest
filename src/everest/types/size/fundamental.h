#pragma once

#include <everest/types/size.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Size;

template<>
class Fundamental<Size> final {
public:

  static constexpr bool exists = true;

};

}