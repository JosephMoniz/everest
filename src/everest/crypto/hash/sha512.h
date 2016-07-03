#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/crypto/hash/sha512/digest.h>

namespace everest {

Sha512Digest Sha512(const String& input) noexcept {
  Sha512Digest digest;
  SHA512((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}