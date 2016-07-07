#pragma once

#include <everest/crypto/hash/sha1/sha1_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha1Digest;

template<>
class Hexable<Sha1Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha1Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha1Digest::size);
  }

};

}