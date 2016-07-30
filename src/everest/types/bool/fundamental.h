#pragma once

#include <everest/types/bool.h>
#include <everest/traits/unlawful/fundamental.h>

namespace everest {

class Bool;

template<>
class Fundamental<Bool> final {
public:

  static constexpr bool exists = true;

};

}