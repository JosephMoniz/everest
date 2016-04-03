#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class F, class T>
class Containable {

  typedef Containable<F, T> Base;

public:

  static constexpr bool exists = false;

  static constexpr bool Contains(const T& n, const F& f) {
    return Base::Contains(n, f);
  }

};

template<class F, class T>
inline bool Contains(const T& n, const F& f) {
  return Containable<F, T>::Contains(n, f);
}

}

#pragma clang diagnostic pop