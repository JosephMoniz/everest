#pragma once

#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha384Digest;

template <>
class Shows<HmacSha384Digest> final {
public:

  static constexpr bool exists = true;

  static String Show(const HmacSha384Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}