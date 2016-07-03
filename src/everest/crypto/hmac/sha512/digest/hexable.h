#pragma once

#include <everest/crypto/hmac/sha512/digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha512Digest;

template<>
class Hexable<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha512Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha512Digest::size);
  }

};

}
