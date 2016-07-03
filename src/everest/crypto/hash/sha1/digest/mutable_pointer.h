#pragma once

#include <everest/crypto/hash/sha1/digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha1Digest;

template<>
class MutablePointable<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha1Digest& digest) noexcept {
    return digest.Value();
  }

};


}