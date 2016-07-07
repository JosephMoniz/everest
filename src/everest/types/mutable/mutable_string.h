#pragma once

#include <everest/memory/memory.h>
#include <everest/memory/growable_memory.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/storable.h>

namespace everest {

class MutableString final {

  friend class Container<MutableString>;
  friend class Takeable<MutableString>;
  friend class Semigroup<MutableString>;
  friend class Pointable<MutableString>;
  friend class Storable<MutableString>;

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

};

template <>
class Storable<MutableString> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Capacity(const MutableString& string) noexcept {
    return Container<GrowableMemory<char>>::Length(string._data);
  }

  static constexpr size_t Occupied(const MutableString& string) noexcept {
    return string._occupied;
  }

};

}

#include <everest/types/mutable/string/pointable.h>
#include <everest/types/mutable/string/container.h>
#include <everest/types/mutable/string/copyable.h>
#include <everest/types/mutable/string/eq.h>
#include <everest/types/mutable/string/hashable.h>
#include <everest/types/mutable/string/iteration.h>
#include <everest/types/mutable/string/semigroup.h>
#include <everest/types/mutable/string/takeable.h>
