#pragma once

#include <everest/crypto/hmac/sha512/hmac_sha512_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha512Digest;

template<>
class Pointable<HmacSha512Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha512Digest& digest) noexcept {
    return digest.Value();
  }

};

}
