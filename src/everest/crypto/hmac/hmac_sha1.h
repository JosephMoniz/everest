#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha1/digest.h>

namespace everest {

HmacSha1Digest HmacSha1(const String& key, const String& input) noexcept {
  HmacSha1Digest digest;
  auto size = HmacSha1Digest::size;
  HMAC(
    EVP_sha1(),
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