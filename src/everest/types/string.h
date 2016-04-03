#pragma once

#include <stddef.h>
#include <utility>

#include <everest/containers/mutable/mutable_memory.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/takeable.h>

namespace everest {

class String {

  friend class Semigroup<String>;

  MutableMemory<char> _memory;

  size_t _length;

public:

  String(const char* str) noexcept {
    size_t length   = 0;
    size_t capacity = 0;
    for (capacity = 0; str[capacity]; capacity++) {
      if ((str[capacity] & 0b11000000) != 0b10000000) {
        length++;
      }
    }
    _length = length;
    _memory = MutableMemory<char>(str, capacity + 1);
  }

  String(MutableMemory<char>&& memory, size_t length) noexcept : _memory(std::move(memory)),
                                                                 _length(length) { }

  String(const String& other) noexcept : _length(other._length) {
    _memory = MutableMemory<char>(other._memory.Pointer(), other._memory.Length());
  }

  String(String&& other) noexcept : _memory(std::move(other._memory)),
                                    _length(std::move(other._length)) { }

  String& operator=(const String& other) noexcept {
    _memory = other._memory;
    _length = other._length;
    return *this;
  }

  String& operator=(String&& other) noexcept {
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
    return Length() == (Capacity() - 1);
  }

};

using SharedString = Shared<String>;

SharedString MakeSharedString(const char* pointer) {
  return MakeShared<String>(pointer);
}

template<>
class Eq<String> {
public:

  static constexpr bool exists = true;

  static bool Equals(const String& lhs, const String& rhs) noexcept {
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
class Takeable<String> {
public:

  static constexpr bool exists = true;

  static const String Take(const String& inString, size_t size) noexcept {
    if (inString.Length() <= size) {
      return inString;
    } else {
      auto string = inString.CString();
      if (inString.IsByteAligned()) {
        auto memory = MutableMemory<char>(string, size + 1);
        memory.MutablePointer()[size] = '\0';
        return String(std::move(memory), size);
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
        return String(std::move(memory), length);
      }
    }
  }

  static const String TakeWhile(const String& n, Predicate<char> p) noexcept {
    return String("TODO"); // TODO
  }

};

template<>
class Semigroup<String> {
public:

  static constexpr bool exists = true;

  static const String Add(const String& lhs, const String& rhs) noexcept {
    auto lCapacity  = lhs.Capacity() - 1;
    auto capacity   = lCapacity + rhs.Capacity();
    auto memory     = MutableMemory<char>(capacity);
    auto lPointer   = lhs._memory.Pointer();
    auto rPointer   = rhs._memory.Pointer();
    auto srcPointer = memory.MutablePointer();
    for (size_t i = 0; i < lCapacity; i++) {
      srcPointer[i] = lPointer[i];
    }
    for (size_t i = lCapacity , j = 0; i < capacity; i++, j++) {
      srcPointer[i] = rPointer[j];
    }
    return String(std::move(memory), capacity - 1);
  }

};

}

