#pragma once

#include <everest/crypto/hash/sha384/sha384_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha384Digest;

template<>
class MutablePointable<Sha384Digest> final {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha384Digest& digest) noexcept {
    return digest.Value();
  }

};


}