#ifndef TRAITOROUS_TYPES_STRING_H
#define TRAITOROUS_TYPES_STRING_H

#include <stddef.h>
#include <utility>

#include <containers/memory.h>
#include <traits/lawful/semigroup.h>
#include <traits/unlawful/eq.h>
#include <traits/unlawful/takeable.h>

namespace traitorous {

class LocalString {

  friend class Semigroup<LocalString>;

  LocalMemory<char> _memory;

  size_t _length;

public:

  LocalString(const char* str) noexcept {
    size_t length   = 0;
    size_t capacity = 0;
    for (capacity = 0; str[capacity]; capacity++) {
      if ((str[capacity] & 0b11000000) != 0b10000000) {
        length++;
      }
    }
    _length = length;
    _memory = LocalMemory<char>(str, capacity + 1);
  }

  LocalString(LocalMemory<char>&& memory, size_t length) noexcept : _memory(std::move(memory)),
                                                                    _length(length) {}

  LocalString(const LocalString& other) noexcept : _memory(other._memory),
                                                   _length(other._length) { }

  LocalString(LocalString&& other) noexcept : _memory(std::move(other._memory)),
                                              _length(std::move(other._length)) { }

  LocalString& operator=(const LocalString& other) noexcept {
    _memory = other._memory;
    _length = other._length;
    return *this;
  }

  LocalString& operator=(LocalString&& other) noexcept {
    _memory = std::move(other._memory);
    _length = other._length;
    other._length = 0;
    return *this;
  }

  const char* CString() const noexcept {
    return _memory.Pointer();
  }

  size_t Length() const noexcept {
    return _length;
  }

  size_t Capacity() const noexcept {
    return _memory.Length();
  }

  bool IsByteAligned() const noexcept {
    return Length() == Capacity();
  }

};

using String = Shared<LocalString>;

String MakeString(const char* pointer) {
  return MakeShared<LocalString>(pointer);
}

template<>
class Eq<LocalString> {
public:

  static constexpr bool exists = true;

  static bool Equals(const LocalString& lhs, const LocalString& rhs) noexcept {
    if (lhs.Length() != rhs.Length() || lhs.Capacity() != rhs.Capacity()) {
      return false;
    } else {
      auto lPointer = lhs.CString();
      auto rPointer = rhs.CString();
      auto capacity = lhs.Capacity();
      for (size_t i = 0; i < capacity; i++) {
        if (lPointer[i] != rPointer[i]) {
          return false;
        }
      }
      return true;
    }
  }

};

template<>
class Takeable<LocalString> {
public:

  static constexpr bool exists = true;

  static const LocalString Take(const LocalString& n, size_t size) noexcept {
    if (n.Length() <= size) {
      return n;
    } else {
      auto str        = n.CString();
      size_t length   = 0;
      size_t capacity = 0;
      for (capacity = 0; str[capacity] && length < size; capacity++) {
        if ((str[capacity] & 0b11000000) != 0b10000000) {
          length++;
        }
      }
      auto memory = LocalMemory<char>(n.CString(), ++capacity);
      memory.MutablePointer()[capacity] = '\0';
      return LocalString(std::move(memory), length);
    }
  }

  static const LocalString TakeWhile(const LocalString& n, Predicate<char> p) noexcept {
    return LocalString("TODO"); // TODO
  }

};

template<>
class Semigroup<LocalString> {
public:

  static constexpr bool exists = true;

  static const LocalString Add(const LocalString& lhs, const LocalString& rhs) noexcept {
    auto lCapacity  = lhs.Capacity() - 1;
    auto capacity   = lCapacity + rhs.Capacity();
    auto memory     = LocalMemory<char>(capacity);
    auto lPointer   = lhs._memory.Pointer();
    auto rPointer   = rhs._memory.Pointer();
    auto srcPointer = memory.MutablePointer();
    for (size_t i = 0; i < lCapacity; i++) {
      srcPointer[i] = lPointer[i];
    }
    for (size_t i = lCapacity , j = 0; i < capacity; i++, j++) {
      srcPointer[i] = rPointer[j];
    }
    return LocalString(std::move(memory), capacity - 1);
  }

};

}

#endif
