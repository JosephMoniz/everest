#pragma once

#include <utility>

namespace everest {

template <class T>
class Sink {

  typedef Sink<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static auto PushThrough(U&& item, T& sink) noexcept {
    static_assert(exists, "T does not implement Sink");
    return Base::PushThrough(std::forward<U>(item), sink);
  }

  static auto CloseSink(T& sink) noexcept {
    static_assert(exists, "T does not implement Sink");
    return Base::CloseSink(sink);
  }

};

template <class T, class U>
auto PushThrough(U&& item, T& sink) noexcept -> decltype(Sink<T>::PushThrough(std::forward<U>(item), sink)) {
  static_assert(Sink<T>::exists, "T does not implement Sink");
  return Sink<T>::PushThrough(std::forward<U>(item), sink);
}

template <class T>
auto CloseSink(T& sink) noexcept -> decltype(Sink<T>::CloseSink(sink)) {
  static_assert(Sink<T>::exists, "T does not implement Sink");
  return Sink<T>::CloseSink(sink);
}

};