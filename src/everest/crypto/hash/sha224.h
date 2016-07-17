#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/crypto/hash/sha224/sha224_sink.h>

namespace everest {

Sha224Digest Sha224(const String& input) noexcept {
  Sha224Digest digest;
  SHA224((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

Sha224Sink Sha224() noexcept {
  return Sha224Sink();
}

}