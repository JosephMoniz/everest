#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class T>
class TPSet {

  friend class Semigroup<TPSet<T>>;

  Set<T> _fresh;

  Set<T> _tombs;

public:

  TPSet() noexcept : _fresh(), _tombs() { }

  TPSet(const TPSet<T>& other) = delete;

  TPSet(TPSet<T>&& other) noexcept : _fresh(std::move(other._fresh)),
                                     _tombs(std::move(other._tombs)) { }

  TPSet(Set<T>&& fresh, Set<T>&& tombs) noexcept : _fresh(std::move(fresh)),
                                                   _tombs(std::move(tombs)) { }

  TPSet insert(T&& item) noexcept {
    return TPSet(Put(std::move(item), _fresh), Copy(_tombs));
  }

  TPSet remove(T&& item) noexcept {
    return TPSet(Copy(_fresh), Put(std::move(item), _tombs));
  }

  Set<T> Value() const noexcept {
    return _fresh - _tombs;
  }

};

template<class T>
class Shows<TPSet<T>> {
public:

  static constexpr bool exists = true;

  static String Show(const TPSet<T>& set) noexcept {
    return String("TPSet(") + Shows<Set<T>>::Show(set.Value()) + String(")");
  }

};

template<class T>
class Eq<TPSet<T>> {
public:

  static constexpr bool exists = true;

  static bool Equals(const TPSet<T>& lhs, const TPSet<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<TPSet<T>> {
public:

  static constexpr bool exists = true;

  static constexpr TPSet<T> Zero() {
    return TPSet();
  }

};

template<class T>
class Semigroup<TPSet<T>> {
public:

  static constexpr bool exists = true;

  static constexpr TPSet<T> Add(const TPSet<T>& lhs, const TPSet<T>& rhs) noexcept {
    return TPSet(lhs._fresh + rhs._fresh, lhs._tombs + rhs._tombs);
  }

};

template<class T>
class Monoid<TPSet<T>> {
public:

  static constexpr bool exists = true;

};

}