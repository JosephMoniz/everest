#pragma once

#include <everest/memory/memory.h>
#include <everest/memory/growable_memory.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/takeable.h>

namespace everest {

class MutableString final {

  friend class Takeable<MutableString>;
  friend class Semigroup<MutableString>;

  GrowableMemory<char> _data;

  size_t _length;

  size_t _occupied;

  static constexpr bool IsLetterByte(char byte) noexcept {
    return (byte & 0b11000000) != 0b10000000;
  }

public:

  MutableString() noexcept : MutableString("\0") { }

  MutableString(const char* str) noexcept : _data() {
    size_t length   = 0;
    size_t capacity = 0;
    for (capacity = 0; str[capacity]; capacity++) {
      if ((str[capacity] & 0b11000000) != 0b10000000) {
        length++;
      }
    }
    _length   = length;
    _occupied = capacity + 1;
    _data.ReserveAtLeast(_occupied);
    memcpy(MutablePointer(_data), str, _occupied);
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
    return Container<GrowableMemory<char>>::Length(_data);
  }

  size_t Occupied() const noexcept {
    return _occupied;
  }

  bool Equals(const MutableString& other) const noexcept {
    if (_length != other.Length() || _occupied != other.Occupied()) {
      return false;
    } else {
      return memcmp(Pointable<GrowableMemory<char>>::Pointer(_data), other.Pointer(), _occupied) == 0;
    }
  }

  template <class F>
  void ForEach(const F& function) const noexcept {
    auto length  = _occupied;
    auto pointer = Pointable<GrowableMemory<char>>::Pointer(_data);
    for (size_t i = 0; i < length; i++) {
      function(pointer[i]);
    }
  }

  unsigned int Hash() const noexcept {
    unsigned int result = 37;
    this->ForEach([&](char item) {
      result = 37 * result + (int) item;
    });
    return result;
  }

  const char* Pointer() const noexcept {
    return Pointable<GrowableMemory<char>>::Pointer(_data);
  }

};

}
