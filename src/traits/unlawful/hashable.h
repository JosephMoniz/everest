#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_HASHABLE
#define TRAITOROUS_TRAITS_HASHABLE 1

namespace traitorous {

template <class T>
class hashable {
  typedef hashable<T> base;
public:

  static constexpr int hash(const T& n) {
    return base::hash(n);
  }

  static constexpr bool exists = false;

};

template <class T, class = std::enable_if<hashable<T>::exists>>
constexpr int hash(const T& n) {
  return hashable<T>::hash(n);
}

}

#endif

#pragma clang diagnostic pop