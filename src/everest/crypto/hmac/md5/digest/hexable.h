#pragma once

#include <everest/crypto/hmac/md5/hmac_md5_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacMd5Digest;

template<>
class Hexable<HmacMd5Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacMd5Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacMd5Digest::size);
  }

};

}