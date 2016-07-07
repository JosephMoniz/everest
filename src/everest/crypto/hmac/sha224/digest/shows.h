#pragma once

#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha224Digest;

template <>
class Shows<HmacSha224Digest> final {
public:

  static constexpr bool exists = true;

  static String Show(const HmacSha224Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}