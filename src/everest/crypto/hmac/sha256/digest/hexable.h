#pragma once

#include <everest/crypto/hmac/sha256/digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha256Digest;

template<>
class Hexable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha256Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha256Digest::size);
  }

};

}