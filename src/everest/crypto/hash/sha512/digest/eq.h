#pragma once

#include <string.h>
#include <everest/crypto/hash/sha512/sha512_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha512Digest;

template<>
class Eq<Sha512Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha512Digest& lhs, const Sha512Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha512Digest::size) == 0;
  }

};

}