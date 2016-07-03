#pragma once

#include <string.h>
#include <openssl/md5.h>
#include <everest/crypto/hash/md5/digest.h>

namespace everest {

Md5Digest Md5(const String& input) noexcept {
  Md5Digest digest;
  MD5((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}