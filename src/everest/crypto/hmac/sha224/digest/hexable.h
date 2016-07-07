#pragma once

#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha224Digest;

template<>
class Hexable<HmacSha224Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha224Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha224Digest::size);
  }

};

}