#pragma once

#include <string.h>
#include <everest/crypto/hmac/sha256/hmac_sha256_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha256Digest;

template<>
class Eq<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha256Digest& lhs, const HmacSha256Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha256Digest::size) == 0;
  }

};

}