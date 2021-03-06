#pragma once

#include <everest/containers/set.h>
#include <everest/traits/unlawful/associative.h>
#include <everest/traits/unlawful/copyable.h>

namespace everest {

template<class T>
class TPSet final {

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

  TPSet Insert(T&& item) noexcept {
    return TPSet(Put(std::move(item), _fresh), Copy(_tombs));
  }

  TPSet Remove(T&& item) noexcept {
    return TPSet(Copy(_fresh), Put(std::move(item), _tombs));
  }

  Set<T> Value() const noexcept {
    return _fresh - _tombs;
  }

};

template<class T>
class Shows<TPSet<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const TPSet<T>& set) noexcept {
    return String("TPSet(") + Shows<Set<T>>::Show(set.Value()) + String(")");
  }

};

template<class T>
class Eq<TPSet<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const TPSet<T>& lhs, const TPSet<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<TPSet<T>> final {
public:

  static constexpr bool exists = true;

  static TPSet<T> Zero() {
    return TPSet();
  }

};

template<class T>
class Semigroup<TPSet<T>> final {
public:

  static constexpr bool exists = true;

  static TPSet<T> Add(const TPSet<T>& lhs, const TPSet<T>& rhs) noexcept {
    return TPSet(lhs._fresh + rhs._fresh, lhs._tombs + rhs._tombs);
  }

};

template<class T>
class Monoid<TPSet<T>> final {
public:

  static constexpr bool exists = true;

};

}