#pragma once

#include <type_traits>

namespace everest {

template <class T>
class Funnel {

  typedef Funnel<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static auto PerformFunnel(U&& item, T& sink) noexcept {
    return Base::PerformFunnel(std::forward<U>(item), sink);
  }

};

template <class T, class U>
auto PerformFunnel(U&& item, T& sink) noexcept -> decltype(Funnel<T>::PerformFunnel(std::forward<U>(item), sink)) {
  static_assert(Funnel<T>::exists, "T does not implement Funnel");
  return Funnel<T>::PerformFunnel(std::forward<U>(item), sink);
}


}