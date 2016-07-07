#pragma once

#include <string.h>
#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Sha224Digest;

template<>
class Eq<Sha224Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha224Digest& lhs, const Sha224Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha224Digest::size) == 0;
  }

};

}