#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/sha224/hmac_sha224_digest.h>
#include <everest/crypto/hmac/sha224/hmac_sha224_sink.h>

namespace everest {

HmacSha224Digest HmacSha224(const String& key, const String& input) noexcept {
  HmacSha224Digest digest;
  auto size = HmacSha224Digest::size;
  HMAC(
    EVP_sha224(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacSha224Sink HmacSha224(const String& key) noexcept {
  return HmacSha224Sink(key);
}

}