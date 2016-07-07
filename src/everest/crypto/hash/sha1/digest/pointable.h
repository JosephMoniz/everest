#pragma once

#include <everest/crypto/hash/sha1/sha1_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha1Digest;

template<>
class Pointable<Sha1Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha1Digest& digest) noexcept {
    return digest.Value();
  }

};

}