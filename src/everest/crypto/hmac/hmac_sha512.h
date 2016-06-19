#pragma once

#include <openssl/hmac.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacSha512Digest final {

  unsigned char _digest[64];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacSha512Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacSha512Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacSha512Digest& lhs, const HmacSha512Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacSha512Digest::size) == 0;
  }

};

template<>
class Hexable<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacSha512Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacSha512Digest::size);
  }

};

template <>
class Shows<HmacSha512Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const HmacSha512Digest& digest) noexcept {
    return ToHex(digest);
  }

};

HmacSha512Digest HmacSha512(const String& key, const String& input) noexcept {
  HmacSha512Digest digest;
  auto size = HmacSha512Digest::size;
  HMAC(
    EVP_sha512(),
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