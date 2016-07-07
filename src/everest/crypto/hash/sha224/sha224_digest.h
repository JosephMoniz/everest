#pragma once

#include <cstddef>

namespace everest {

class Sha224Digest final {

  unsigned char _digest[28];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hash/sha224/digest/pointable.h>
#include <everest/crypto/hash/sha224/digest/eq.h>
#include <everest/crypto/hash/sha224/digest/hexable.h>
#include <everest/crypto/hash/sha224/digest/mutable_pointer.h>
#include <everest/crypto/hash/sha224/digest/shows.h>