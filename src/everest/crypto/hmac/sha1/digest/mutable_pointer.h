#pragma once

#include <everest/crypto/hmac/sha1/hmac_sha1_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha1Digest;

template<>
class MutablePointable<HmacSha1Digest> final {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha1Digest& digest) noexcept {
    return digest.Value();
  }

};

}