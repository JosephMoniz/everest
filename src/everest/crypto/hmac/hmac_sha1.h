#pragma once

#include <openssl/hmac.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha1Digest final {

  unsigned char _digest[20];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha1Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha1Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha1Digest& lhs, const HmacSha1Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha1Digest::size) == 0;
  }

};

template<>
class Hexable<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha1Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha1Digest::size);
  }

};

template <>
class Shows<HmacSha1Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const HmacSha1Digest& digest) noexcept {
    return ToHex(digest);
  }

};

HmacSha1Digest HmacSha1(const String& key, const String& input) noexcept {
  HmacSha1Digest digest;
  auto size = HmacSha1Digest::size;
  HMAC(
    EVP_sha1(),
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