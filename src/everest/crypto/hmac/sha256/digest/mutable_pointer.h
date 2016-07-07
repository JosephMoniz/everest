#pragma once

#include <everest/crypto/hmac/sha256/hmac_sha256_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha256Digest;

template<>
class MutablePointable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha256Digest& digest) noexcept {
    return digest.Value();
  }

};

}