#pragma once

#include <utility>

namespace everest {

template <class T, class U>
class MutableTuple final {

  friend class Eq<MutableTuple<T, U>>;
  friend class Copyable<MutableTuple<T, U>>;
  friend class Ord<MutableTuple<T, U>>;
  friend class Shows<MutableTuple<T, U>>;

  T _first;

  U _second;

public:

  MutableTuple() : _first(), _second() {}

  MutableTuple(T&& first, U&& second) noexcept : _first(std::move(first)),
                                                 _second(std::move(second)) { }

  T& First() noexcept {
    return _first;
  }

  const T& ConstFirst() const noexcept {
    return _first;
  }

  U& Second() noexcept {
    return _second;
  }

  const U& ConstSecond() const noexcept {
    return _second;
  }

};

}