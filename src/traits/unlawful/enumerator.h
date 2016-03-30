#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"


namespace traitorous {

template<class T>
class Enumerator {

  typedef Enumerator<T> Base;

public:

  static constexpr bool exists = false;

  static const Option <T> Next(const T& enumerator) {
    return Base::Next(enumerator);
  }

};

template<class T>
static const Option <T> Next(const T& enumerator) noexcept {
  return Enumerator<T>::Next(enumerator);
};

}

#pragma clang diagnostic pop
