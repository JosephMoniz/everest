#pragma once

#include <everest/crypto/hash/sha256/sha256_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha256Digest;

template<>
class Pointable<Sha256Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha256Digest& digest) noexcept {
    return digest.Value();
  }

};

}