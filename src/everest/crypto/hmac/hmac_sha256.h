#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha256/digest.h>

namespace everest {

HmacSha256Digest HmacSha256(const String& key, const String& input) noexcept {
  HmacSha256Digest digest;
  auto size = HmacSha256Digest::size;
  HMAC(
    EVP_sha256(),
    Pointer(key),
    (int) Length(key),
    (const unsigned char*)Pointer(input),
    Length(input),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

}