#ifndef TRAITOROUS_TRAITS_UNLAWFUL_ENUMERABLE_H
#define TRAITOROUS_TRAITS_UNLAWFUL_ENUMERABLE_H

namespace traitorous {

template<class T>
struct Enumerable {

  typedef Enumerable<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static U Enumerator(const T& enumerable) noexcept {
    return Base::Enumerator(enumerable);
  }

};

template<class T>
auto Enumerator(const T& enumerable) noexcept -> decltype(Enumerable<T>::Enumerator(enumerable)) {
  return Enumerable<T>::Enumerator(enumerable);
};

}

#endif

