#pragma once

#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha224Digest;

template<>
class Pointable<HmacSha224Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha224Digest& digest) noexcept {
    return digest.Value();
  }

};

}