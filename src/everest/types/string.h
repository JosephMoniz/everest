#pragma once

#include <stddef.h>
#include <utility>

#include <everest/memory/memory.h>
#include <everest/memory/mutable_memory.h>
#include <everest/traits/unlawful/one.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/takeable.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/iteration.h>
#include <everest/traits/unlawful/pointable.h>
#include <everest/traits/unlawful/hashable.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

class String final {

  friend class Container<String>;
  friend class Semigroup<String>;

  Memory<char> _memory;

  size_t _length;

public:

  String() noexcept : _memory(),
                      _length() { }

  String(const char* str) noexcept {
    size_t length   = 0;
    size_t capacity = 0;
    for (capacity = 0; str[capacity]; capacity++) {
      if ((str[capacity] & 0b11000000) != 0b10000000) {
        length++;
      }
    }
    _length = length;
    _memory = Memory<char>(str, capacity + 1);
  }

  String(MutableMemory<char>&& memory, size_t length) noexcept : _memory(std::move(memory)),
                                                                 _length(length) { }

  String(Memory<char>&& memory, size_t length) noexcept : _memory(std::move(memory)),
                                                          _length(length) { }

  String(const String& other) noexcept : _length(other._length) {
    _memory = Memory<char>(Pointer(other._memory), Length(other._memory));
  }

  String(String&& other) noexcept : _memory(std::move(other._memory)),
                                    _length(std::move(other._length)) { }

  String& operator=(const String& other) noexcept {
    _memory = Memory<char>(Pointer(other._memory), Length(other._memory));
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
    return Pointer(_memory);
  }

  size_t Capacity() const noexcept {
    return Length(_memory);
  }

  bool IsByteAligned() const noexcept {
    return _length == (Capacity() - 1);
  }

};

using SharedString = Shared<String>;

SharedString MakeSharedString(const char* pointer) {
  return MakeShared<String>(pointer);
}

template <>
class Container<String> {
public:

static constexpr bool exists = true;

static constexpr size_t Length(const String& string) noexcept {
  return string._length;
}

static constexpr bool IsEmpty(const String& string) noexcept {
  return string._length == 0;
}

};

template<>
class Eq<String> {
public:

  static constexpr bool exists = true;

  static bool Equals(const String& lhs, const String& rhs) noexcept {
    if (Length(lhs) != Length(rhs) || lhs.Capacity() != rhs.Capacity()) {
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

  static const String Take(size_t size, const String& inString) noexcept {
    if (Length(inString) <= size) {
      return inString;
    } else {
      auto string = inString.CString();
      if (inString.IsByteAligned()) {
        auto memory = MutableMemory<char>(string, size + 1);
        MutablePointer(memory)[size] = '\0';
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
        MutablePointer(memory)[length] = '\0';
        return String(std::move(memory), length);
      }
    }
  }

  static const String TakeWhile(Predicate<char> predicate, const String& string) noexcept {
    size_t offset = 0;
    size_t length = Length(string);
    auto pointer  = string.CString();
    while (offset < length && predicate(pointer[offset])) {
      offset++;
    }
    auto memory = MutableMemory<char>(pointer, offset + 1);
    MutablePointer(memory)[length] = '\0';
    return String(std::move(memory), length);
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
    auto lPointer   = Pointer(lhs._memory);
    auto rPointer   = Pointer(rhs._memory);
    auto srcPointer = MutablePointer(memory);
    for (size_t i = 0; i < lCapacity; i++) {
      srcPointer[i] = lPointer[i];
    }
    for (size_t i = lCapacity , j = 0; i < capacity; i++, j++) {
      srcPointer[i] = rPointer[j];
    }
    return String(std::move(memory), capacity - 1);
  }

};

template<>
class Pointable<String> {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const String& string) noexcept {
    return string.CString();
  }
};


template<>
class Iteration<String> {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const String& string, const F& function) noexcept {
    auto length  = string.Capacity();
    auto pointer = Pointer(string);
    for (size_t i = 0; i < length; i++) {
      function(pointer[i]);
    }
  }

};

template<>
class Hashable<String> {
public:

  static constexpr bool exists = true;

  static int Hash(const String& string) noexcept {
    int result = 37;
    ForEach(string, [&](char item) {
      result = 37 * result + (int) item;
    });
    return result;
  }

};

template <class T>
class Shows;

template <>
class Shows<String> {
public:

  static constexpr bool exists = true;

  static const String& Show(const String& string) noexcept {
    return string;
  }

};

template<>
class Copyable<String> {
public:

  static constexpr bool exists = true;

  static String Copy(String string) noexcept {
    return String(string);
  }

};


}

