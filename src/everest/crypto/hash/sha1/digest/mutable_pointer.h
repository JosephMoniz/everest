#pragma once

#include <everest/crypto/hash/sha1/sha1_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha1Digest;

template<>
class MutablePointable<Sha1Digest> final {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha1Digest& digest) noexcept {
    return digest.Value();
  }

};


}