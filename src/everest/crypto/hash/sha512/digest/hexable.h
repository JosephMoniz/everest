#pragma once

#include <everest/crypto/hash/sha512/sha512_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha512Digest;

template<>
class Hexable<Sha512Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha512Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha512Digest::size);
  }

};

}