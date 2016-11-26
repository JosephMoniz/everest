#pragma once
#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"

namespace everest {

template <class T>
class Containable {

  typedef Containable<T> Base;

public:

  static constexpr bool exists = false;

  template<class U>
  static bool Contains(const U& n, const T& f) {
    static_assert(exists, "T does not implement Containable");
    return Base::Contains(n, f);
  }

};

template<class U, class T>
bool Contains(const U& n, const T& f) {
  static_assert(Containable<T>::exists, "T does not implement Containable");
  return Containable<T>::Contains(n, f);
}

}

#pragma clang diagnostic pop