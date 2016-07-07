#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/crypto/hash/sha384/sha384_digest.h>
#include <everest/crypto/hash/sha384/sha384_sink.h>

namespace everest {

Sha384Digest Sha384(const String& input) noexcept {
  Sha384Digest digest;
  SHA384((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

Sha384Sink Sha384() noexcept {
  return Sha384Sink();
}

}