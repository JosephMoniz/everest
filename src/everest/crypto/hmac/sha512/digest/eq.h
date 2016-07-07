#pragma once

#include <string.h>
#include <everest/crypto/hmac/sha512/hmac_sha512_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha512Digest;

template<>
class Eq<HmacSha512Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha512Digest& lhs, const HmacSha512Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha512Digest::size) == 0;
  }

};

}
