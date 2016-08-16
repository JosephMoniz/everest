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

  GSet<T> Add(const GSet<T>& rhs) const noexcept {
    return GSet(_set + rhs.Value());
  }

  String Show() const noexcept {
    return String("GSet(") + _set.Show() + String(")");
  }

  bool Equals(const GSet<T>& rhs) const noexcept {
    return _set.Equals(rhs.Value());
  }

  static GSet<T> Zero() {
    return GSet<T>();
  }

};

template<class T>
class Shows<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const GSet<T>& set) noexcept {
    return set.Show();
  }

};

template<class T>
class Eq<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const GSet<T>& lhs, const GSet<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static GSet<T> Zero() {
    return GSet<T>::Zero();
  }

};

template<class T>
class Semigroup<GSet<T>> final {
public:

  static constexpr bool exists = true;

  static GSet<T> Add(const GSet<T>& lhs, const GSet<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<GSet<T>> final {
public:

  static constexpr bool exists = true;

};

}