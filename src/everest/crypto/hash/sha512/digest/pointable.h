#pragma once

#include <everest/crypto/hash/sha512/sha512_digest.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha512Digest;

template<>
class Pointable<Sha512Digest> final {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha512Digest& digest) noexcept {
    return digest.Value();
  }

};

}