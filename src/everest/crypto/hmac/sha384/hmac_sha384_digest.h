#pragma once

#include <cstddef>

namespace everest {

class HmacSha384Digest final {

  unsigned char _digest[48];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hmac/sha384/digest/pointable.h>
#include <everest/crypto/hmac/sha384/digest/eq.h>
#include <everest/crypto/hmac/sha384/digest/hexable.h>
#include <everest/crypto/hmac/sha384/digest/mutable_pointer.h>
#include <everest/crypto/hmac/sha384/digest/shows.h>