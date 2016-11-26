#pragma once

#include <everest/memory/memory.h>
#include <everest/memory/growable_memory.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/types/expressive/hash_value.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/ord/ordering.h>

namespace everest {

class MutableString final {

  friend class Takeable<MutableString>;
  friend class Semigroup<MutableString>;

  GrowableMemory<char> _data;

  size_t _length;

  size_t _occupied;

public:

  MutableString() noexcept : MutableString("\0") { }

  MutableString(const char* str) noexcept : _data() {
    size_t length   = 0;
    size_t capacity = 0;
    for (capacity = 0; str[capacity]; capacity++) {
      if (IsLetterByte(str[capacity])) {
        length++;
      }
    }
    _length   = length;
    _occupied = capacity + 1;
    _data.ReserveAtLeast(_occupied);
    memcpy(_data.MutablePointer(), str, _occupied);
  }

  MutableString(const MutableString& other) = delete;

  MutableString(MutableString&& other) noexcept : _data(std::move(other._data)),
                                                  _length(other._length),
                                                  _occupied(other._occupied) { }


  MutableString(MutableMemory<char>&& memory,
                size_t length,
                size_t occupied) noexcept : _data(std::move(memory)),
                                            _length(length),
                                            _occupied(occupied) { }

  MutableString(Memory<char>&& memory,
                size_t length,
                size_t occupied) noexcept : _data(std::move(memory)),
                                            _length(length),
                                            _occupied(occupied) { }

  MutableString& operator=(MutableString&& other) noexcept {
    _data     = std::move(other._data);
    _length   = other._length;
    _occupied = other._occupied;
    other._length = 0;
    return *this;
  }

  static bool IsLetterByte(char byte) noexcept {
    return (byte & 0b11000000) != 0b10000000;
  }

  bool IsByteAligned() const noexcept {
    return _length == (_occupied - 1);
  }

  size_t Length() const noexcept {
    return _length;
  }

  bool IsEmpty() const noexcept {
    return _length == 0;
  }

  size_t Capacity() const noexcept {
    return _data.Length();
  }

  size_t Occupied() const noexcept {
    return _occupied;
  }

  bool Equals(const MutableString& other) const noexcept {
    if (_length != other.Length() || _occupied != other.Occupied()) {
      return false;
    } else {
      return memcmp(_data.Pointer(), other.Pointer(), _occupied) == 0;
    }
  }

  Ordering Compare(const MutableString& other) const noexcept {
    auto otherLength = other.Length();
    if (otherLength == _length) {
      auto lhsPointer = Pointer();
      auto rhsPointer = other.Pointer();
      for (size_t i = 0; i < _length; i++) {
        auto left  = lhsPointer[i];
        auto right = rhsPointer[i];
        if (left < right) {
          return Ordering::LESS;
        } else {
          if (left > right) {
            return Ordering::GREATER;
          }
        }
      }
      return Ordering::EQUAL;
    } else {
      if (_length < otherLength) {
        return Ordering::LESS;
      } else {
        return Ordering::GREATER;
      }
    }
  }

  const MutableString& Min(const MutableString& other) const noexcept {
    return (Compare(other) == Ordering::GREATER)
      ? other
      : *this;
  }

  const MutableString& Max(const MutableString& other) const noexcept {
    return (Compare(other) == Ordering::LESS)
      ? other
      : *this;
  }

  template <class F>
  void ForEach(F function) const noexcept {
    auto length  = _occupied - 1;
    auto pointer = _data.Pointer();
    for (size_t i = 0; i < length; i++) {
      function(pointer[i]);
    }
  }

  HashValue Hash() const noexcept {
    unsigned int result = 37;
    ForEach([&](char item) {
      result = 37 * result + (int) item;
    });
    return HashValue(result);
  }

  char* MutablePointer() noexcept {
    return _data.MutablePointer();
  }

  const char* Pointer() const noexcept {
    return _data.Pointer();
  }

  MutableString Copy() const noexcept {
    return MutableString(Pointer());
  }

  MutableString Add(const MutableString& other) const noexcept {
    auto lOccupied   = Occupied() - 1;
    auto occupied    = lOccupied + other.Occupied();
    auto memory      = MutableMemory<char>(occupied);
    auto lPointer    = Pointer();
    auto rPointer    = other.Pointer();
    auto destPointer = memory.MutablePointer();
    memcpy(destPointer, lPointer, lOccupied);
    memcpy(&destPointer[lOccupied], rPointer, other.Occupied());
    return MutableString(std::move(memory), Length() + other.Length(), occupied);
  }

  // TODO: Make trait
  // TODO: Make test
  MutableString& AddInPlace(const MutableString& other) noexcept {
    auto lOccupied = Occupied() - 1;
    auto occupied  = lOccupied + other.Occupied();
    _data.ReserveAtLeast(occupied);
    auto lPointer  = _data.MutablePointer();
    auto rPointer  = other.Pointer();
    memcpy(&lPointer[lOccupied], rPointer, other.Occupied());
    _length   = Length() + other.Length();
    _occupied = occupied;
    return *this;
  }

  // TODO: Make trait
  // TODO: Make test
  // TODO: Optimize, this is a lame hack
  MutableString& AddInPlace(const char* other) noexcept {
    return AddInPlace(MutableString(other));
  }

  MutableString Take(size_t size) const noexcept {
    if (Length() <= size) {
      return Copy();
    } else {
      auto string = Pointer();
      if (IsByteAligned()) {
        auto occupied = size + 1;
        auto memory   = MutableMemory<char>(string, occupied);
        memory.MutablePointer()[size] = '\0';
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
        memory.MutablePointer()[length] = '\0';
        return MutableString(std::move(memory), length, capacity);
      }
    }
  }

  MutableString TakeWhile(Predicate<char> predicate) const noexcept {
    size_t offset = 0;
    size_t length = Length();
    auto pointer  = Pointer();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    auto occupied = offset + 1;
    auto memory   = MutableMemory<char>(pointer, occupied);
    memory.MutablePointer()[offset] = '\0';
    return MutableString(std::move(memory), length, occupied);
  }

  template <class F>
  void VisitByteSlice(F visitor) const noexcept {
    visitor(Pointer(), Length(), Occupied() - 1, IsByteAligned());
  };

};

}
