#pragma once

#include <everest/crypto/hash/sha256/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha256Digest;

template <>
class Shows<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const Sha256Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}