#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/takeable.h>

namespace everest {

class MutableString;

template<>
class Takeable<MutableString> final {
public:

  static constexpr bool exists = true;

  static MutableString Take(size_t size, const MutableString& inString) noexcept {
    if (Length(inString) <= size) {
      return Copy(inString);
    } else {
      auto string = Pointer(inString);
      if (inString.IsByteAligned()) {
        auto occupied = size + 1;
        auto memory   = MutableMemory<char>(string, occupied);
        MutablePointer(memory)[size] = '\0';
        return MutableString(std::move(memory), size, occupied);
      } else {
        size_t length   = 0;
        size_t capacity = 0;
        for (capacity = 0; string[capacity] && length < size; capacity++) {
          if ((string[capacity] & 0b11000000) != 0b10000000) {
            length++;
          }
        }
        auto memory = MutableMemory<char>(string, ++capacity);
        MutablePointer(memory)[length] = '\0';
        return MutableString(std::move(memory), length, capacity);
      }
    }
  }

  static MutableString Take(size_t size, MutableString&& inString) noexcept {
    if (Length(inString) <= size) {
      return std::move(inString);
    } else {
      if (inString.IsByteAligned()) {
        MutablePointer(inString._data)[size] = '\0';
        inString._length                     = size;
        inString._occupied                   = size + 1;
        return std::move(inString);
      } else {
        auto string     = Pointer(inString);
        size_t length   = 0;
        size_t capacity = 0;
        for (capacity = 0; string[capacity] && length < size; capacity++) {
          if ((string[capacity] & 0b11000000) != 0b10000000) {
            length++;
          }
        }
        MutablePointer(inString._data)[capacity] = '\0';
        inString._length                         = size;
        inString._occupied                       = capacity;
        return std::move(inString);
      }
    }
  }

  static MutableString TakeWhile(Predicate<char> predicate, const MutableString& string) noexcept {
    size_t offset = 0;
    size_t length = Length(string);
    auto pointer  = Pointer(string);
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    auto occupied = offset + 1;
    auto memory   = MutableMemory<char>(pointer, occupied);
    MutablePointer(memory)[offset] = '\0';
    return MutableString(std::move(memory), length, occupied);
  }

  static MutableString TakeWhile(Predicate<char> predicate, MutableString&& string) noexcept {
    size_t offset = 0;
    size_t length = 0;
    size_t size   = Length(string);
    auto pointer  = MutablePointer(string._data);
    while (offset < size && predicate(pointer[offset])) {
      if (MutableString::IsLetterByte(pointer[offset])) {
        length++;
      }
      offset++;
    }
    auto occupied    = offset + 1;
    pointer[offset]  = '\0';
    string._occupied = occupied;
    string._length   = length;
    return std::move(string);
  }

};

}