#pragma once

#include <everest/crypto/hash/md5/digest.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Md5Digest;

template <>
class Shows<Md5Digest> {
public:

  static constexpr bool exists = true;

  static String Show(const Md5Digest& digest) noexcept {
    return ToHex(digest);
  }

};

}