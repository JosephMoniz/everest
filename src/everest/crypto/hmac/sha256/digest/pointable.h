#pragma once

#include <everest/crypto/hmac/sha256/digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha256Digest;

template<>
class Pointable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha256Digest& digest) noexcept {
    return digest.Value();
  }

};

}