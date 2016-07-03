#pragma once

#include <everest/crypto/hash/sha512/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha512Digest;

template <>
class Shows<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const Sha512Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}