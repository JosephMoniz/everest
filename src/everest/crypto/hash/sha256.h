#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/crypto/hash/sha256/sha256_digest.h>
#include <everest/crypto/hash/sha256/sha256_sink.h>

namespace everest {

Sha256Digest Sha256(const String& input) noexcept {
  Sha256Digest digest;
  SHA256((const unsigned char*)input.Pointer(), input.Length(), digest.Value());
  return digest;
}

Sha256Sink Sha256() noexcept {
  return Sha256Sink();
}

}