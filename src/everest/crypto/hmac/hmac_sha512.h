#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha512/hmac_sha512_digest.h>

namespace everest {

HmacSha512Digest HmacSha512(const String& key, const String& input) noexcept {
  HmacSha512Digest digest;
  auto size = HmacSha512Digest::size;
  HMAC(
    EVP_sha512(),
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