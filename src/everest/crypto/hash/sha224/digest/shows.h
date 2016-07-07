#pragma once

#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha224Digest;

template <>
class Shows<Sha224Digest> final {
public:

  static constexpr bool exists = true;

  static String Show(const Sha224Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}