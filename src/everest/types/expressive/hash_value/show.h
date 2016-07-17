#pragma once

#include <everest/types/expressive/hash_value.h>
#include <everest/traits/unlawful/show.h>

namespace everest {

class HashValue;

template <>
class Shows<HashValue> final {
public:

  static constexpr bool exists = true;

  static String Show(HashValue hash) noexcept {
    return Shows<unsigned int>::Show(hash.Value());
  }

};

}