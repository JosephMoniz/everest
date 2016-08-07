#pragma once

#include <everest/containers/map.h>
#include <everest/crdt/counters/pncounter.h>
#include <everest/types/string.h>
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

  friend class Semigroup<PNACounter<T>>;

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
    ForEach(_actors, [&](MutableMapEntry<String, T>& entry) {
      result = result + entry.Value().Value();
    });
  }

};

template<class T>
class Shows<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const PNACounter<T>& counter) noexcept {
    return String("PNACounter(") + Shows<T>::Show(counter.Value()) + String(")");
  }

};

template<class T>
class Eq<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const PNACounter<T>& lhs, const PNACounter<T>& rhs) noexcept {
    return lhs.Value() == rhs.Value();
  }

};

template<class T>
class ZeroVal<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNACounter<T> Zero() {
    return PNACounter(Map());
  }

};

template<class T>
class Semigroup<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

  static PNACounter<T> Add(const PNACounter<T>& lhs, const PNACounter<T>& rhs) noexcept {
    return PNACounter(lhs._actors + rhs._actors);
  }

};

template<class T>
class Monoid<PNACounter<T>> final {
public:

  static constexpr bool exists = true;

};

}
