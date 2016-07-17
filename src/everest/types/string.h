#pragma once

#include <stddef.h>
#include <utility>

#include <everest/memory/memory.h>
#include <everest/memory/mutable_memory.h>
#include <everest/types/mutable/mutable_string.h>

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

  template <class F>
  void ForEach(const F& function) const noexcept {
    _wrapped.ForEach(function);
  }

  unsigned int Hash() const noexcept {
    return _wrapped.Hash();
  }

};

}

