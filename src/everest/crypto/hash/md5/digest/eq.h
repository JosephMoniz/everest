#pragma once

#include <string.h>
#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

class Md5Digest;

template<>
class Eq<Md5Digest> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const Md5Digest& lhs, const Md5Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Md5Digest::size) == 0;
  }

};

}