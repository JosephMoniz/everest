#pragma once

#include <string.h>
#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha224Digest;

template<>
class Eq<HmacSha224Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha224Digest& lhs, const HmacSha224Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha224Digest::size) == 0;
  }

};

}