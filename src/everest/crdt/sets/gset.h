#pragma once

#include <everest/containers/set.h>

namespace everest {

template<class T>
class GSet final {

  Set<T> _set;

public:

  GSet() noexcept : _set() { }

  GSet(const GSet<T>& other) = delete;

  GSet(GSet<T>&& other) noexcept : _set(std::move(other._set)) { }

  GSet(Set<T>&& set) noexcept : _set(std::move(set)) { }

  Set<T>& Value() const noexcept {
    return _set;
  }

};

template<class T>
class Shows<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GSet<T>& set) noexcept {
    return String("GSet(") + Shows<Set<T>>::Show(set.Value()) + String(")");
  }

};

template<class T>
class Eq<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GSet<T>& lhs, const GSet<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static GSet<T> Zero() {
    return GSet();
  }

};

template<class T>
class Semigroup<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static GSet<T> Add(const GSet<T>& lhs, const GSet<T>& rhs) noexcept {
    return GSet(lhs.Value() + rhs.Value());
  }

};

template<class T>
class Monoid<GSet<T>> final {
public:

  static constexpr bool exists = true;

};

}