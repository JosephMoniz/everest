#pragma once

#include <everest/types/size.h>
#include <everest/traits/lawful/monoid.h>

namespace everest {

class Size;

template <>
class Monoid<Size> final {
public:

  static constexpr bool exists = true;

};

}