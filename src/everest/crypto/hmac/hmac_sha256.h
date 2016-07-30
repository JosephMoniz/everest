#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha256/hmac_sha256_digest.h>
#include <everest/crypto/hmac/sha256/hmac_sha256_sink.h>

namespace everest {

HmacSha256Digest HmacSha256(const String& key, const String& input) noexcept {
  HmacSha256Digest digest;
  auto size = HmacSha256Digest::size;
  HMAC(
    EVP_sha256(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacSha256Sink HmacSha256(const String& key) noexcept {
  return HmacSha256Sink(key);
}

}