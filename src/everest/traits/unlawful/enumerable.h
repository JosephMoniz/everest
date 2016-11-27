#pragma once

namespace everest {


template<class T>
class Enumerable {

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
  static_assert(Enumerable<T>::exists, "T does not implement Enumerable");
  return Enumerable<T>::Enumerate(e);
};

}


