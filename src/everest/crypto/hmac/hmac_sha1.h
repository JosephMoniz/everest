#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha1/hmac_sha1_digest.h>
#include <everest/crypto/hmac/sha1/hmac_sha1_sink.h>

namespace everest {

HmacSha1Digest HmacSha1(const String& key, const String& input) noexcept {
  HmacSha1Digest digest;
  auto size = HmacSha1Digest::size;
  HMAC(
    EVP_sha1(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacSha1Sink HmacSha1(const String& key) noexcept {
  return HmacSha1Sink(key);
}

}