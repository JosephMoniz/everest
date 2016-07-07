#pragma once

#include <string.h>
#include <openssl/md5.h>
#include <everest/crypto/hash/md5/md5_digest.h>
#include <everest/crypto/hash/md5/md5_sink.h>

namespace everest {

Md5Digest Md5(const String& input) noexcept {
  Md5Digest digest;
  MD5((const unsigned char*)Pointer(input), Length(input), MutablePointer(digest));
  return digest;
}

Md5Sink Md5() noexcept {
  return Md5Sink();
}

}