#pragma once

namespace traitorous {


template<class T>
struct Enumerable {

  typedef Enumerable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static U Enumerate(const T& enumerable) noexcept {
    return Base::Enumerate(enumerable);
  }

};

template<class T>
auto Enumerate(const T& e) noexcept -> decltype(Enumerable<T>::Enumerate(e)) {
  return Enumerable<T>::Enumerate(e);
};

}


