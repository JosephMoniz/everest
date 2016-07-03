#pragma once

#include <everest/crypto/hmac/sha512/digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class HmacSha512Digest;

template<>
class MutablePointable<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha512Digest& digest) noexcept {
    return digest.Value();
  }

};

}
