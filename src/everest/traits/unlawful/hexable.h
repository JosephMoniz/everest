#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

#include <everest/types/string.h>

namespace everest {

template <class T>
class Hexable {

  typedef Hexable<T> Base;

public:

  static constexpr bool exists = false;

  static String ToHex(const T& n) noexcept {
    return Base::ToHex(n);
  }

};

template <class T>
String ToHex(const T& hashable) noexcept {
  return Hexable<T>::ToHex(hashable);
}

String ToHexFromBigEndianBytePointer(unsigned char* pointer, size_t bytes) {
  auto nibbleToHex = "0123456789abcdef";
  auto length      = bytes * 2;
  auto memory      = Memory<char>(length + 1);
  auto destination = memory.MutablePointer();
  for (size_t i = 0; i < bytes; i++) {
    auto offset = 2 * i;
    auto byte   = pointer[i];
    destination[offset]     = nibbleToHex[byte >> 4];
    destination[offset + 1] = nibbleToHex[byte & 0b00001111];
  }
  destination[length] = '\0';
  return String(std::move(memory), length);
}

String ToHexFromLittleEndianBytePointer(unsigned char* pointer, size_t bytes) {
  auto nibbleToHex = "0123456789abcdef";
  auto length      = bytes * 2;
  auto memory      = Memory<char>(length + 1);
  auto destination = memory.MutablePointer();
  for (size_t i = 0; i < bytes; i++) {
    auto offset = length - (2 * i) - 2;
    auto byte   = pointer[i];
    destination[offset]     = nibbleToHex[byte >> 4];
    destination[offset + 1] = nibbleToHex[byte & 0b00001111];
  }
  destination[length] = '\0';
  return String(std::move(memory), length);
}

}

#pragma clang diagnostic pop
