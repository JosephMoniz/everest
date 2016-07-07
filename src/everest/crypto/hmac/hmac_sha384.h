#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>

namespace everest {

HmacSha384Digest HmacSha384(const String& key, const String& input) noexcept {
  HmacSha384Digest digest;
  auto size = HmacSha384Digest::size;
  HMAC(
    EVP_sha384(),
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