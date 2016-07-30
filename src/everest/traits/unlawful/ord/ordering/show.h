#pragma once

#include <everest/traits/unlawful/ord/ordering.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

template<>
class Shows<Ordering> {
public:

  static constexpr bool exists = true;

  static String Show(Ordering n) noexcept {
    switch(n) {
      case Ordering::LESS:    return String("LESS");
      case Ordering::EQUAL:   return String("EQUAL");
      case Ordering::GREATER: return String("GREATER");
    }
  }

};

}