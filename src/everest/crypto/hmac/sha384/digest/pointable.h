#pragma once

#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha384Digest;

template<>
class Pointable<HmacSha384Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha384Digest& digest) noexcept {
    return digest.Value();
  }

};

}