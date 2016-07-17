#pragma once

#include <everest/types/expressive/hash_value.h>
#include <everest/traits/unlawful/eq.h>

namespace everest {

class HashValue;

template<>
class Eq<HashValue> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const HashValue& lhs, const HashValue& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

}