#pragma once

#include <everest/crypto/hmac/sha1/digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacSha1Digest;

template<>
class Pointable<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha1Digest& digest) noexcept {
    return digest.Value();
  }

};

}