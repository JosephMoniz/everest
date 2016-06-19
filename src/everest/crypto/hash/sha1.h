#pragma once

#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha1Digest final {

  unsigned char _digest[20];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha1Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha1Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha1Digest& lhs, const Sha1Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha1Digest::size) == 0;
  }

};

template<>
class Hexable<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha1Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha1Digest::size);
  }

};

template <>
class Shows<Sha1Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const Sha1Digest& digest) noexcept {
    return ToHex(digest);
  }

};

Sha1Digest Sha1(const String& input) noexcept {
  Sha1Digest digest;
  SHA1((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}