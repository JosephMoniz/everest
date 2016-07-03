#pragma once

#include <everest/crypto/hash/md5/digest.h>
#include <everest/traits/unlawful/mutable/mutable_pointer.h>

namespace everest {

class Md5Digest;

template<>
class MutablePointable<Md5Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Md5Digest& digest) noexcept {
    return digest.Value();
  }

};

}