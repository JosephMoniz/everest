#pragma once

#include <everest/crypto/hash/sha256/digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha256Digest;

template<>
class MutablePointable<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha256Digest& digest) noexcept {
    return digest.Value();
  }

};

}