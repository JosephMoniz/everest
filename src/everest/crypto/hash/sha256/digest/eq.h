#pragma once

#include <string.h>
#include <everest/crypto/hash/sha256/sha256_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha256Digest;

template<>
class Eq<Sha256Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha256Digest& lhs, const Sha256Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha256Digest::size) == 0;
  }

};

}