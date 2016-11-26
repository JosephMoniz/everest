#pragma once

#include <stddef.h>
#include <utility>

#include <everest/memory/memory.h>
#include <everest/memory/mutable_memory.h>
#include <everest/strings/mutable_string.h>
#include <everest/types/expressive/hash_value.h>

namespace everest {

class String final {

  friend class Semigroup<String>;
  friend class Takeable<String>;

  MutableString _wrapped;

public:

  String() noexcept : _wrapped() { }

  String(const char* str) noexcept : _wrapped(str) { }

  String(MutableMemory<char>&& memory,
         size_t length,
         size_t occupied) noexcept : _wrapped(std::move(memory), length, occupied) { }

  String(Memory<char>&& memory,
         size_t length,
         size_t occupied) noexcept : _wrapped(std::move(memory), length, occupied) { }

  String(const String& other) = delete;

  String(String&& other) noexcept : _wrapped(std::move(other._wrapped)) { }

  String(MutableString&& string) noexcept : _wrapped(std::move(string)) { }

  String& operator=(const String& other) = delete;

  String& operator=(String&& other) noexcept {
    _wrapped = std::move(other._wrapped);
    return *this;
  }

  static bool IsLetterByte(char byte) noexcept {
    return MutableString::IsLetterByte(byte);
  }

  bool IsByteAligned() const noexcept {
    return _wrapped.IsByteAligned();
  }

  const char* Pointer() const noexcept {
    return _wrapped.Pointer();
  }

  size_t Capacity() const noexcept {
    return _wrapped.Capacity();
  }

  size_t Occupied() const noexcept {
    return _wrapped.Occupied();
  }

  size_t Length() const noexcept {
    return _wrapped.Length();
  }

  bool IsEmpty() const noexcept {
    return _wrapped.IsEmpty();
  }

  bool Equals(const String& other) const noexcept {
    return _wrapped.Equals(other._wrapped);
  }

  Ordering Compare(const String& other) const noexcept {
    return _wrapped.Compare(other._wrapped);
  }

  const String& Min(const String& other) const noexcept {
    return Compare(other) == Ordering::LESS
      ? *this
      : other;
  }

  const String& Max(const String& other) const noexcept {
    return Compare(other) == Ordering::GREATER
      ? *this
      : other;
  }

  template <class F>
  void ForEach(F function) const noexcept {
    _wrapped.ForEach(function);
  }

  HashValue Hash() const noexcept {
    return _wrapped.Hash();
  }

  String Copy() const noexcept {
    return String(Pointer());
  }

  String Add(const String& other) const noexcept {
    return String(_wrapped.Add(other._wrapped));
  }

  String Take(size_t size) const noexcept {
    return String(_wrapped.Take(size));
  }

  String TakeWhile(Predicate<char> predicate) const noexcept {
    return String(_wrapped.TakeWhile(predicate));
  }

  template <class F>
  void VisitByteSlice(F visitor) const noexcept {
    visitor(Pointer(), Length(), Occupied() - 1, IsByteAligned());
  };

  class StringBuilder final {

    MutableString _string;

  public:

    StringBuilder() noexcept : _string() { }

    StringBuilder& Add(const char* string) noexcept {
      _string.AddInPlace(string);
      return *this;
    }

    StringBuilder& Add(const String& string) noexcept {
      _string.AddInPlace(string._wrapped);
      return *this;
    }

    StringBuilder& Add(const MutableString& string) noexcept {
      _string.AddInPlace(string);
      return *this;
    }

    String Build() noexcept {
      return String(std::move(_string));
    }

  };

  static StringBuilder Builder() noexcept {
    return StringBuilder();
  }

};

}

