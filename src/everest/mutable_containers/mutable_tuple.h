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

  MutableTuple(MutableTuple<T, U>&& other) noexcept : _first(std::move(other._first)),
                                                      _second(std::move(other._second)) { }

  MutableTuple<T, U>& operator=(const MutableTuple<T, U>& other) = delete;

  MutableTuple<T, U>& operator=(MutableTuple<T, U>&& other) noexcept {
    _first  = std::move(other._first);
    _second = std::move(other._second);
    return *this;
  }

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