#pragma once

namespace everest {

class Sha256Digest final {

  unsigned char _digest[32];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hash/sha256/digest/pointable.h>
#include <everest/crypto/hash/sha256/digest/eq.h>
#include <everest/crypto/hash/sha256/digest/hexable.h>
#include <everest/crypto/hash/sha256/digest/mutable_pointer.h>
#include <everest/crypto/hash/sha256/digest/shows.h>