#pragma once

#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha384Digest;

template<>
class Hexable<HmacSha384Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha384Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha384Digest::size);
  }

};

}