#pragma once

#include <string.h>
#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha384Digest;

template<>
class Eq<HmacSha384Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha384Digest& lhs, const HmacSha384Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha384Digest::size) == 0;
  }

};

}