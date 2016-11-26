#pragma once

#include <everest/containers/set.h>

namespace everest {

template<class T>
class GrowOnlySet final {

  Set<T> _set;

public:

  GrowOnlySet() noexcept : _set() { }

  GrowOnlySet(const GrowOnlySet<T>& other) = delete;

  GrowOnlySet(GrowOnlySet<T>&& other) noexcept : _set(std::move(other._set)) { }

  GrowOnlySet(Set<T>&& set) noexcept : _set(std::move(set)) { }

  Set<T>& Value() const noexcept {
    return _set;
  }

  GrowOnlySet<T> Add(const GrowOnlySet<T>& rhs) const noexcept {
    return GrowOnlySet(_set + rhs.Value());
  }

  String Show() const noexcept {
    return String("GSet(") + _set.Show() + String(")");
  }

  bool Equals(const GrowOnlySet<T>& rhs) const noexcept {
    return _set.Equals(rhs.Value());
  }

  static GrowOnlySet<T> Zero() {
    return GrowOnlySet<T>();
  }

};

template<class T>
class Shows<GrowOnlySet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GrowOnlySet<T>& set) noexcept {
    return set.Show();
  }

};

template<class T>
class Eq<GrowOnlySet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GrowOnlySet<T>& lhs, const GrowOnlySet<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<GrowOnlySet<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlySet<T> Zero() {
    return GrowOnlySet<T>::Zero();
  }

};

template<class T>
class Semigroup<GrowOnlySet<T>> final {
public:

  static constexpr bool exists = true;

  static GrowOnlySet<T> Add(const GrowOnlySet<T>& lhs, const GrowOnlySet<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<GrowOnlySet<T>> final {
public:

  static constexpr bool exists = true;

};

}