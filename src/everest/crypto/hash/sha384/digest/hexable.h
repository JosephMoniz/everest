#pragma once

#include <everest/crypto/hash/sha384/sha384_digest.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha384Digest;

template<>
class Hexable<Sha384Digest> final {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha384Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha384Digest::size);
  }

};

}