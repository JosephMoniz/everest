#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/strings/string.h>

namespace everest {

template <class T>
class Hexable {

  typedef Hexable<T> Base;

public:

  static constexpr bool exists = false;

  static String ToHex(const T& n) noexcept {
    static_assert(exists, "T does not implement Hexable");
    return Base::ToHex(n);
  }

};

template <class T>
String ToHex(const T& hashable) noexcept {
  static_assert(Hexable<T>::exists, "T does not implement Hexable");
  return Hexable<T>::ToHex(hashable);
}

String ToHexFromBigEndianBytePointer(unsigned char* pointer, size_t bytes) {
  auto nibbleToHex = "0123456789abcdef";
  auto length      = bytes * 2;
  auto memory      = MutableMemory<char>(length + 1);
  auto destination = memory.MutablePointer();
  for (size_t i = 0; i < bytes; i++) {
    auto offset = 2 * i;
    auto byte   = pointer[i];
    destination[offset]     = nibbleToHex[byte >> 4];
    destination[offset + 1] = nibbleToHex[byte & 0b00001111];
  }
  destination[length] = '\0';
  return String(std::move(memory), length, length + 1);
}

String ToHexFromLittleEndianBytePointer(unsigned char* pointer, size_t bytes) {
  auto nibbleToHex = "0123456789abcdef";
  auto length      = bytes * 2;
  auto memory      = MutableMemory<char>(length + 1);
  auto destination = memory.MutablePointer();
  for (size_t i = 0; i < bytes; i++) {
    auto offset = length - (2 * i) - 2;
    auto byte   = pointer[i];
    destination[offset]     = nibbleToHex[byte >> 4];
    destination[offset + 1] = nibbleToHex[byte & 0b00001111];
  }
  destination[length] = '\0';
  return String(std::move(memory), length, length + 1);
}

}

#pragma clang diagnostic pop
