#pragma once

namespace everest {

class HmacMd5Digest final {

  unsigned char _digest[16];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

}

#include <everest/crypto/hmac/md5/digest/pointable.h>
#include <everest/crypto/hmac/md5/digest/eq.h>
#include <everest/crypto/hmac/md5/digest/hexable.h>
#include <everest/crypto/hmac/md5/digest/mutable_pointer.h>
#include <everest/crypto/hmac/md5/digest/shows.h>