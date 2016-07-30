#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/md5/hmac_md5_digest.h>
#include <everest/crypto/hmac/md5/hmac_md5_sink.h>

namespace everest {

HmacMd5Digest HmacMd5(const String& key, const String& input) noexcept {
  HmacMd5Digest digest;
  auto size = HmacMd5Digest::size;
  HMAC(
    EVP_md5(),
    key.Pointer(),
    (int) key.Length(),
    (const unsigned char*)input.Pointer(),
    input.Length(),
    digest.Value(),
    (unsigned int*) &size
  );
  return digest;
}

HmacMd5Sink HmacMd5(const String& key) noexcept {
  return HmacMd5Sink(key);
}

}