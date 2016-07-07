#pragma once

namespace everest {

class HmacSha1Digest final {

  unsigned char _digest[20];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hmac/sha1/digest/pointable.h>
#include <everest/crypto/hmac/sha1/digest/eq.h>
#include <everest/crypto/hmac/sha1/digest/hexable.h>
#include <everest/crypto/hmac/sha1/digest/mutable_pointer.h>
#include <everest/crypto/hmac/sha1/digest/shows.h>