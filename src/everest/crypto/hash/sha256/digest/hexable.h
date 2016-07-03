#pragma once

#include <everest/crypto/hash/sha256/digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha256Digest;

template<>
class Hexable<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha256Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha256Digest::size);
  }

};

}