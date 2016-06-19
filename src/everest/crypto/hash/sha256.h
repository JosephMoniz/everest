#pragma once

#include <openssl/sha.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Sha256Digest final {

  unsigned char _digest[32];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Sha256Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Sha256Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Sha256Digest& lhs, const Sha256Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Sha256Digest::size) == 0;
  }

};

template<>
class Hexable<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Sha256Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Sha256Digest::size);
  }

};

template <>
class Shows<Sha256Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const Sha256Digest& digest) noexcept {
    return ToHex(digest);
  }

};

Sha256Digest Sha256(const String& input) noexcept {
  Sha256Digest digest;
  SHA256((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}