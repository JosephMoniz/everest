#pragma once

#include <string.h>
#include <everest/crypto/hash/sha1/digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha1Digest;

template<>
class Eq<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha1Digest& lhs, const Sha1Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha1Digest::size) == 0;
  }

};

}