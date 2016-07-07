#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>

namespace everest {

HmacSha224Digest HmacSha224(const String& key, const String& input) noexcept {
  HmacSha224Digest digest;
  auto size = HmacSha224Digest::size;
  HMAC(
    EVP_sha224(),
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