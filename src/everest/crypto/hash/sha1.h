#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/crypto/hash/sha1/digest.h>

namespace everest {

Sha1Digest Sha1(const String& input) noexcept {
  Sha1Digest digest;
  SHA1((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}