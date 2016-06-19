#pragma once

#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha512Digest final {

  unsigned char _digest[64];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha512Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha512Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha512Digest& lhs, const Sha512Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha512Digest::size) == 0;
  }

};

template<>
class Hexable<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha512Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha512Digest::size);
  }

};

template <>
class Shows<Sha512Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const Sha512Digest& digest) noexcept {
    return ToHex(digest);
  }

};

Sha512Digest Sha512(const String& input) noexcept {
  Sha512Digest digest;
  SHA512((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}