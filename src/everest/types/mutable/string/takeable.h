#pragma once

#include <everest/types/mutable/mutable_string.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/types/mutable/string/copyable.h>

namespace everest {

class MutableString;

template<>
class Takeable<MutableString> final {
public:

  static constexpr bool exists = true;

  static MutableString Take(size_t size, const MutableString& inString) noexcept {
    return inString.Take(size);
  }

  static MutableString Take(size_t size, MutableString&& inString) noexcept {
    if (inString.Length() <= size) {
      return std::move(inString);
    } else {
      if (inString.IsByteAligned()) {
        inString._data.MutablePointer()[size] = '\0';
        inString._length                     = size;
        inString._occupied                   = size + 1;
        return std::move(inString);
      } else {
        auto string     = inString.Pointer();
        size_t length   = 0;
        size_t capacity = 0;
        for (capacity = 0; string[capacity] && length < size; capacity++) {
          if ((string[capacity] & 0b11000000) != 0b10000000) {
            length++;
          }
        }
        inString._data.MutablePointer()[capacity] = '\0';
        inString._length                         = size;
        inString._occupied                       = capacity;
        return std::move(inString);
      }
    }
  }

  static MutableString TakeWhile(Predicate<char> predicate, const MutableString& string) noexcept {
    return string.TakeWhile(predicate);
  }

  static MutableString TakeWhile(Predicate<char> predicate, MutableString&& string) noexcept {
    size_t offset = 0;
    size_t length = 0;
    size_t size   = string.Length();
    auto pointer  = string._data.MutablePointer();
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