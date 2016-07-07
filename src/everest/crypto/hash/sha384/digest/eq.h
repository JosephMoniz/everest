#pragma once

#include <string.h>
#include <everest/crypto/hash/sha384/sha384_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha384Digest;

template<>
class Eq<Sha384Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha384Digest& lhs, const Sha384Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha384Digest::size) == 0;
  }

};

}