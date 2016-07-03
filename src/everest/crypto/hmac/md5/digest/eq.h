#pragma once

#include <string.h>
#include <everest/crypto/hmac/md5/digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class HmacMd5Digest;

template<>
class Eq<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacMd5Digest& lhs, const HmacMd5Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacMd5Digest::size) == 0;
  }

};

}