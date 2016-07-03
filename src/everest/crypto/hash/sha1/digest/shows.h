#pragma once

#include <everest/crypto/hash/sha1/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha1Digest;

template <>
class Shows<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const Sha1Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}