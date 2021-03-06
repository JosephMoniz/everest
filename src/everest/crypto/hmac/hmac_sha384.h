#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha384/hmac_sha384_digest.h>
#include <everest/crypto/hmac/sha384/hmac_sha384_sink.h>

namespace everest {

HmacSha384Digest HmacSha384(const String& key, const String& input) noexcept {
  HmacSha384Digest digest;
  auto size = HmacSha384Digest::size;
  HMAC(
    EVP_sha384(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacSha384Sink HmacSha384(const String& key) noexcept {
  return HmacSha384Sink(key);
}

}