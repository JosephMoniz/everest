#pragma once

#include <everest/traits/unlawful/mutable/mutable_associative.h>
#include <everest/containers/option.h>
#include <everest/mutable_containers/mutable_map.h>
#include <everest/mutable_crdt/counters/mutable_gcounter.h>
#include <everest/traits/unlawful/container.h>
#include <everest/traits/unlawful/associative.h>

namespace everest {

template<class A, class T, template <class, class> class InnerMapType = MutableMap>
class MutableGACounter final {

  using Self = MutableGACounter<A, T>;

  using OptionalCounter = Option<MutableGCounter<T>*>;

  using InnerCounter = MutableGCounter<T>;

  using InnerMap = InnerMapType<A, MutableGCounter<T>>;

  using InnerMapEntry = MutableMapEntry<A, MutableGCounter<T>>;

  A _actorIdentifier;

  InnerMap _actors;

public:

  MutableGACounter(A&& actorIdentifier) noexcept : _actorIdentifier(std::move(actorIdentifier)),
                                                              _actors() {}

  MutableGACounter(A&& actorIdentifier,
                   const T& number) noexcept : _actorIdentifier(std::move(actorIdentifier)),
                                               _actors()
  {
    _actors.PutInPlace(Copyable<A>::Copy(actorIdentifier), number);
  }

  MutableGACounter(A&& actorIdentifier,
                   InnerMap&& actors) noexcept : _actorIdentifier(std::move(actorIdentifier)),
                                                 _actors(std::move(actors)) { }

  MutableGACounter(const Self& other) = delete;

  MutableGACounter(Self&& other) noexcept : _actorIdentifier(std::move(other._actorIdentifier)),
                                            _actors(std::move(other._actors)) {}

  Self& operator=(const Self& other) = delete;

  Self& operator=(Self&& other) noexcept {
    _actorIdentifier = std::move(other._actorIdentifier);
    _actors          = std::move(other._actors);
    return *this;
  }

  Self Copy() const noexcept {
    return Self(Copyable<A>::Copy(_actorIdentifier), _actors.Copy());
  }

  Self& Increment() noexcept {
    return IncrementBy(OneVal<T>::One());
  }

  Self& IncrementBy(const T& number) noexcept {
    OptionalCounter value = _actors.GetInPlace(_actorIdentifier);
    if (IsEmpty(value)) {
      _actors.PutInPlace(Copyable<A>::Copy(_actorIdentifier), InnerCounter(number));
      return *this;
    } else {
      value.GetMutable()->IncrementBy(number);
      return *this;
    }
  }

  T Value() const noexcept {
    auto result = ZeroVal<T>::Zero();
    _actors.ForEach([&](const InnerMapEntry& entry) {
      result += entry.ConstValue().Value();
    });
    return result;
  }

  Self Add(const Self& other) const noexcept {
    return Self(Copyable<T>::Copy(_actorIdentifier), _actors.Add(other._actors));
  }

  Self& AddInPlace(const Self& other) noexcept {
    _actors.AddInPlace(other._actors);
    return *this;
  }

  String Show() const noexcept {
    return String::Builder()
      .Add("MutableGACounter(")
      .Add(Shows<T>::Show(Value()))
      .Add(")")
      .Build();
  }

  bool Equals(const Self& other) const noexcept {
    return Value() == other.Value();
  }

};

template <class A, class T>
class Eq<MutableGACounter<A, T>> final {
public:

  static constexpr bool exists = true;

  static bool Equals(const MutableGACounter<A, T>& lhs,
                     const MutableGACounter<A, T>& rhs) noexcept
  {
    return lhs.Equals(rhs);
  }

};

template <class A, class T>
class Shows<MutableGACounter<A, T>> final {
public:

  static constexpr bool exists = true;

  static String Show(const MutableGACounter<A, T>& counter) noexcept {
    return counter.Show();
  }

};

}