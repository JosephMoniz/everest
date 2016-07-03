#pragma once

#include <everest/crypto/hmac/sha512/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha512Digest;

template <>
class Shows<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const HmacSha512Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}