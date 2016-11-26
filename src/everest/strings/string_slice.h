#pragma once

#include <cstdio>
#include <utility>
#include <everest/types/size.h>

namespace everest {

template <class T>
class StringSlice final {

  T _string;

  size_t _offset;

  size_t _length;

public:

  StringSlice(T&& string, size_t offset, size_t length) noexcept : _string(std::move(string)),
                                                                   _offset(offset),
                                                                   _length(length) { }

  template <class F>
  void VisitByteSlice(F visitor) const noexcept {
    auto toSkip = _offset;
    auto toTake = _length;
    _string.VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      auto skipped         = Size(length).Min(toSkip).Value();
      auto remainingSkip   = toSkip - skipped;
      auto remainingLength = length - skipped;
      auto taken           = Size(remainingLength).Min(toTake);
      auto remainingTake   = toTake - taken;
      if (byteAligned) {
        visitor(&pointer[skipped], taken, taken, byteAligned);
      } else {
        size_t newlyOccupied = 0;
        size_t offset        = 0;
        size_t counter       = 0;
        for (size_t i = 0; i < occupied; i++) {
          if (String::IsLetterByte(pointer[i])) {
            counter++;
            if (counter == taken) {
              offset = counter;
            }
            if (counter > taken) {
              newlyOccupied = counter;
            }
          }
        }
        visitor(&pointer[offset], taken, newlyOccupied, byteAligned);
      }
      toSkip = remainingSkip;
      toTake = remainingTake;
    });
  };

  bool IsByteAligned() const noexcept {
    bool result = false;
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      result = byteAligned;
    });
    return result;
  }

  const char* Pointer() const noexcept {
    const char* result;
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      result = pointer;
    });
    return result;
  }

  size_t Occupied() const noexcept {
    size_t result;
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      result = occupied;
    });
    return result;
  }

  size_t Length() const noexcept {
    size_t result;
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      result = length;
    });
    return result;
  }

  bool IsEmpty() const noexcept {
    bool result;
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      result = length == 0;
    });
    return result;
  }

  template <class F>
  void ForEach(F function) const noexcept {
    VisitByteSlice([&](const char* pointer, size_t length, size_t occupied, bool byteAligned) {
      for (size_t i = 0; i < occupied; i++) {
        function(pointer[i]);
      }
    });
  }

  HashValue Hash() const noexcept {
    unsigned int result = 37;
    ForEach([&](char item) {
      result = 37 * result + (int) item;
    });
    return HashValue(result);
  }

};

}