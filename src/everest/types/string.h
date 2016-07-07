#pragma once

#include <stddef.h>
#include <utility>

#include <everest/memory/memory.h>
#include <everest/memory/mutable_memory.h>
#include <everest/types/mutable/mutable_string.h>
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
#include <everest/traits/unlawful/storable.h>

namespace everest {

class String final {

  friend class Pointable<String>;
  friend class Container<String>;
  friend class Semigroup<String>;
  friend class Eq<String>;
  friend class Iteration<String>;
  friend class Takeable<String>;
  friend class Hashable<String>;
  friend class Storable<String>;

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

};

template<>
class Pointable<String> final {
public:

  static constexpr bool exists = true;

  static const char* Pointer(const String& string) noexcept {
    return Pointable<MutableString>::Pointer(string._wrapped);
  }
};

template<>
class Copyable<String> final {
public:

  static constexpr bool exists = true;

  static String Copy(const String& string) noexcept {
    return String(Pointer(string));
  }

};

template <>
class Storable<String> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Capacity(const String& string) noexcept {
    return Storable<MutableString>::Capacity(string._wrapped);
  }

  static constexpr size_t Occupied(const String& string) noexcept {
    return Storable<MutableString>::Occupied(string._wrapped);
  }

};

template <>
class Container<String> final {
public:

  static constexpr bool exists = true;

  static constexpr size_t Length(const String& string) noexcept {
    return Container<MutableString>::Length(string._wrapped);
  }

  static constexpr bool IsEmpty(const String& string) noexcept {
    return Container<MutableString>::IsEmpty(string._wrapped);
  }

};

template<>
class Eq<String> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const String& lhs, const String& rhs) noexcept {
    return Eq<MutableString>::Equals(lhs._wrapped, rhs._wrapped);
  }

};

template<>
class Takeable<String> final {
public:

  static constexpr bool exists = true;

  static String Take(size_t size, const String& inString) noexcept {
    return String(Takeable<MutableString>::Take(size, inString._wrapped));
  }

  static String Take(size_t size, String&& inString) noexcept {
    return String(Takeable<MutableString>::Take(size, std::move(inString._wrapped)));
  }

  static String TakeWhile(Predicate<char> predicate, const String& string) noexcept {
    return String(Takeable<MutableString>::TakeWhile(predicate, string._wrapped));
  }

};

template<>
class Semigroup<String> final {
public:

  static constexpr bool exists = true;

  static String Add(const String& lhs, const String& rhs) noexcept {
    return String(Semigroup<MutableString>::Add(lhs._wrapped, rhs._wrapped));
  }

  static String Add(String&& lhs, const String& rhs) noexcept {
    return String(Semigroup<MutableString>::Add(std::move(lhs._wrapped), rhs._wrapped));
  }

};


template<>
class Iteration<String> final {
public:

  static constexpr bool exists = true;

  template <class F>
  static void ForEach(const String& string, const F& function) noexcept {
    Iteration<MutableString>::ForEach(string._wrapped, function);
  }

};

template<>
class Hashable<String> final {
public:

  static constexpr bool exists = true;

  static int Hash(const String& string) noexcept {
    return Hashable<MutableString>::Hash(string._wrapped);
  }

};

template <class T>
class Shows;

template <>
class Shows<String> final {
public:

  static constexpr bool exists = true;

  static String Show(const String& string) noexcept {
    return String(Pointer(string));
  }

  static String Show(String&& string) noexcept {
    return std::move(string);
  }

};

}

