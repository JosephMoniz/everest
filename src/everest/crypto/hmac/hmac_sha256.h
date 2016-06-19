#pragma once

#include <openssl/hmac.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha256Digest final {

  unsigned char _digest[32];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha256Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha256Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha256Digest& lhs, const HmacSha256Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha256Digest::size) == 0;
  }

};

template<>
class Hexable<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha256Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha256Digest::size);
  }

};

template <>
class Shows<HmacSha256Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const HmacSha256Digest& digest) noexcept {
    return ToHex(digest);
  }

};

HmacSha256Digest HmacSha256(const String& key, const String& input) noexcept {
  HmacSha256Digest digest;
  auto size = HmacSha256Digest::size;
  HMAC(
    EVP_sha256(),
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