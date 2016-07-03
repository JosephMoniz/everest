#pragma once

namespace everest {

class HmacSha512Digest final {

  unsigned char _digest[64];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hmac/sha512/digest/pointable.h>
#include <everest/crypto/hmac/sha512/digest/eq.h>
#include <everest/crypto/hmac/sha512/digest/hexable.h>
#include <everest/crypto/hmac/sha512/digest/mutable_pointer.h>
#include <everest/crypto/hmac/sha512/digest/shows.h>