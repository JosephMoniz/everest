#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/crypto/hash/sha256/digest.h>

namespace everest {

Sha256Digest Sha256(const String& input) noexcept {
  Sha256Digest digest;
  SHA256((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}