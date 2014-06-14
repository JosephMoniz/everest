#ifndef TRAITOROUS_TRAITS_SHOW
#define TRAITOROUS_TRAITS_SHOW 1

namespace traitorous {

template <class T>
struct shows {
  // std::string str()
  static constexpr bool exists = false;
};

template <class T, class = typename std::enable_if<shows<T>::exists>::type>
const std::string show(const T& n) noexcept {
  return shows<T>::show(n);
}

}

#endif
