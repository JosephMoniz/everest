#pragma once

#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha224Digest;

template<>
class MutablePointable<HmacSha224Digest> final {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha224Digest& digest) noexcept {
    return digest.Value();
  }

};

}