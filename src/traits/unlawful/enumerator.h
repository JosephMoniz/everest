#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_UNLAWFUL_ENUMERATOR_H
#define TRAITOROUS_TRAITS_UNLAWFUL_ENUMERATOR_H


namespace traitorous {

template<class T>
class Enumerator {

  typedef Enumerator<T> Base;

public:

  static constexpr bool exists = false;

  static const LocalOption<T> Next(const T& enumerator) {
    return Base::Next(enumerator);
  }

};

template<class T>
static const LocalOption<T> Next(const T& enumerator) noexcept {
  return Enumerator<T>::Next(enumerator);
};

}

#endif

#pragma clang diagnostic pop
