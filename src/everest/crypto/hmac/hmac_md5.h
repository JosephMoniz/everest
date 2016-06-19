#pragma once

#include <string.h>
#include <openssl/hmac.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class HmacMd5Digest final {

  unsigned char _digest[16];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const HmacMd5Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const HmacMd5Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const HmacMd5Digest& lhs, const HmacMd5Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), HmacMd5Digest::size) == 0;
  }

};

template<>
class Hexable<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const HmacMd5Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), HmacMd5Digest::size);
  }

};

template <>
class Shows<HmacMd5Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const HmacMd5Digest& digest) noexcept {
    return ToHex(digest);
  }

};

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