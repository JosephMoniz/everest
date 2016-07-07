#pragma once

#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Md5Digest;

template <>
class Shows<Md5Digest> final {
public:

  static constexpr bool exists = true;

  static String Show(const Md5Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}