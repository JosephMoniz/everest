#pragma once

#include <everest/containers/map.h>
#include <everest/crdt/counters/pncounter.h>
#include <everest/strings/string.h>
#include <everest/traits/unlawful/show.h>
#include <everest/traits/unlawful/eq.h>
#include <everest/traits/unlawful/ord.h>
#include <everest/traits/unlawful/zero.h>
#include <everest/traits/lawful/monoid.h>
#include <everest/traits/lawful/semigroup.h>
#include <everest/traits/unlawful/bounded.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class T>
class PNACounter final {

  Map<String, PNCounter<T>> _actors;

public:

  PNACounter() noexcept : _actors() { }

  PNACounter(Map<String, PNCounter<T>>&& actors) noexcept : _actors(std::move(actors)) { }

  PNACounter<T> Increment(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PNACounter(Put(std::move(actor), PNCounter<T>(OneVal<T>::One()), _actors))
      : PNACounter(Put(actor, value->Increment(), _actors));
  }

  PNACounter<T> IncrementBy(String&& actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PNACounter(Put(std::move(actor), PNCounter<T>(number), _actors))
      : PNACounter(Put(actor, value->IncrementBy(number), _actors));
  }

  PNACounter<T> Decrement(String&& actor) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PNACounter(Put(std::move(actor), PNCounter<T>().Decrement(), _actors))
      : PNACounter(Put(actor, value->Decrement(), _actors));
  }

  PNACounter<T> DecrementBy(String&& actor, const T& number) const noexcept {
    auto value = Get(actor, _actors);
    return (value == nullptr)
      ? PNACounter(Put(std::move(actor), PNCounter<T>().DecrementBy(number), _actors))
      : PNACounter(Put(actor, value->DecrementBy(number), _actors));
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](MutableMapEntry<String, PNACounter<T>>& entry) {
      result = result + entry.Value().Value();
    });
  }

  PNACounter<T> Add(const PNACounter<T>& other) const noexcept {
    return PNACounter(_actors + other._actors);
  }

  String Show() const noexcept {
    return String("PNACounter(") + Shows<T>::Show(Value()) + String(")");
  }

  bool Equals(const PNACounter<T>& rhs) const noexcept {
    return Value() == rhs.Value();
  }

  static PNACounter<T> Zero() {
    return PNACounter<T>(Map<String, PNCounter<T>>());
  }

};

template<class T>
class Shows<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const PNACounter<T>& counter) noexcept {
    return counter.Show();
  }

};

template<class T>
class Eq<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const PNACounter<T>& lhs, const PNACounter<T>& rhs) noexcept {
    return lhs.Equals(rhs);
  }

};

template<class T>
class ZeroVal<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNACounter<T> Zero() {
    return PNACounter<T>::Zero();
  }

};

template<class T>
class Semigroup<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNACounter<T> Add(const PNACounter<T>& lhs, const PNACounter<T>& rhs) noexcept {
    return lhs.Add(rhs);
  }

};

template<class T>
class Monoid<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
