#pragma once

#include <everest/crypto/hmac/md5/digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacMd5Digest;

template<>
class Pointable<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacMd5Digest& digest) noexcept {
    return digest.Value();
  }

};

}