#pragma once

#include <everest/crypto/hmac/md5/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacMd5Digest;

template <>
class Shows<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const HmacMd5Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}