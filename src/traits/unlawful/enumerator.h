#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_UNLAWFUL_ENUMERATOR_H
#define TRAITOROUS_TRAITS_UNLAWFUL_ENUMERATOR_H


namespace traitorous {

template<class T>
struct Enumerator {

  typedef Enumerator<T> Base;

public:

  static constexpr bool exists = false;

  static bool HasNext(const T& enumerator) const noexcept {
    return Base::HasNext(enumerator);
  }

  static const T& Next(const T& enumerator) {
    return Base::Next(enumerator);
  }

};

template<class T>
static bool HasNext(const T& enumerator) noexcept {
  return Enumerator<T>::HasNext(enumerator);
};

}

#endif

#pragma clang diagnostic pop