#pragma once

#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha224Digest;

template<>
class Hexable<Sha224Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha224Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha224Digest::size);
  }

};

}