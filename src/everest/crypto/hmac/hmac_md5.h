#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/crypto/hmac/md5/hmac_md5_digest.h>

namespace everest {

HmacMd5Digest HmacMd5(const String& key, const String& input) noexcept {
  HmacMd5Digest digest;
  auto size = HmacMd5Digest::size;
  HMAC(
    EVP_md5(),
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