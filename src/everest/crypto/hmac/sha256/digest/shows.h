#pragma once

#include <everest/crypto/hmac/sha256/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha256Digest;

template <>
class Shows<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const HmacSha256Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}