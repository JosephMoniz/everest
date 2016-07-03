#pragma once

#include <string.h>
#include <everest/crypto/hmac/sha1/digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha1Digest;

template<>
class Eq<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha1Digest& lhs, const HmacSha1Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha1Digest::size) == 0;
  }

};

}