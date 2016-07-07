#pragma once

#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Sha224Digest;

template<>
class MutablePointable<Sha224Digest> final {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha224Digest& digest) noexcept {
    return digest.Value();
  }

};


}