#pragma clang diagnostic push
#pragma ide diagnostic ignored "InfiniteRecursion"
#ifndef TRAITOROUS_TRAITS_SHOW
#define TRAITOROUS_TRAITS_SHOW 1

namespace traitorous {

template <class T>
class Shows {

  typedef Shows<T> Base;

public:

  static constexpr bool exists = false;

  template <class U>
  static const inline std::string Show(const U& n) noexcept {
    return Base::Show(n);
  }

};

template <class T>
const inline std::string Show(const T& n) noexcept {
  return Shows<T>::Show(n);
}

}

#endif

#pragma clang diagnostic pop