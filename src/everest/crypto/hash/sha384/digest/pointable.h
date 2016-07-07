#pragma once

#include <everest/crypto/hash/sha384/sha384_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha1Digest;

template<>
class Pointable<Sha384Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha384Digest& digest) noexcept {
    return digest.Value();
  }

};

}