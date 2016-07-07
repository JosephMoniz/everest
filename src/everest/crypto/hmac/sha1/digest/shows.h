#pragma once

#include <everest/crypto/hmac/sha1/hmac_sha1_digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha1Digest;

template <>
class Shows<HmacSha1Digest> final {
public:

  static constexpr bool exists = true;

  static String Show(const HmacSha1Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}