#ifndef TRAITOROUS_TRAITS_CONTAINER
#define TRAITOROUS_TRAITS_CONTAINER 1

namespace traitorous {

template <class T>
struct container {
  // size_t length()
  // bool is_empty()
  static constexpr bool exists = false;
};

template<class T, class = typename std::enable_if<container<T>::exists>::type>
constexpr size_t length(const T& n) noexcept {
  return container<T>::length(n);
}

template<class T, class = typename std::enable_if<container<T>::exists>::type>
constexpr bool is_empty(const T& n) noexcept {
  return container<T>::is_empty(n);
}

}

#endif
