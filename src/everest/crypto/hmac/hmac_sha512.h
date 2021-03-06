#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha512/hmac_sha512_digest.h>
#include <everest/crypto/hmac/sha512/hmac_sha512_sink.h>

namespace everest {

HmacSha512Digest HmacSha512(const String& key, const String& input) noexcept {
  HmacSha512Digest digest;
  auto size = HmacSha512Digest::size;
  HMAC(
    EVP_sha512(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacSha512Sink HmacSha512(const String& key) noexcept {
  return HmacSha512Sink(key);
}

}