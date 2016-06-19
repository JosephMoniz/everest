#pragma once

#include <string.h>
#include <openssl/md5.h>
#include <everest/types/string.h>
#include <everest/traits/unlawful/hexable.h>

namespace everest {

class Md5Digest final {

  unsigned char _digest[16];

public:

  static constexpr size_t size = sizeof(_digest);

  unsigned char* Value() const noexcept {
    return (unsigned char*) _digest;
  }

};

template<>
class Pointable<Md5Digest> {
public:

  static constexpr bool exists = true;

  static const unsigned char* Pointer(const Md5Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class MutablePointable<Md5Digest> {
public:

  static constexpr bool exists = true;

  static unsigned char* Pointer(const Md5Digest& digest) noexcept {
    return digest.Value();
  }

};

template<>
class Eq<Md5Digest> {
public:

  static constexpr bool exists = true;

  static bool Equals(const Md5Digest& lhs, const Md5Digest& rhs) noexcept {
    return memcmp(Pointer(lhs), Pointer(rhs), Md5Digest::size) == 0;
  }

};

template<>
class Hexable<Md5Digest> {
public:

  static constexpr bool exists = true;

  static String ToHex(const Md5Digest& digest) noexcept {
    return ToHexFromBigEndianBytePointer(digest.Value(), Md5Digest::size);
  }

};

template <>
class Shows<Md5Digest> {
public:

  static constexpr bool exists = true;

  static const String Show(const Md5Digest& digest) noexcept {
    return ToHex(digest);
  }

};

Md5Digest Md5(const String& input) noexcept {
  Md5Digest digest;
  MD5((const unsigned char*)Pointer(input), Length(input), digest.Value());
  return digest;
}

}