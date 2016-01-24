#ifndef TRAITOROUS_TRAITS_DISJOINABLE
#define TRAITOROUS_TRAITS_DISJOINABLE 1

namespace traitorous {

template <class T>
struct disjoinable {
  // T disjoin()
  static constexpr bool exists = false;
};

template <class T,
          class = typename std::enable_if<disjoinable<T>::exists>::type>
constexpr inline T disjoin(const T& a, const T& b) noexcept {
  return disjoinable<T>::disjoin(a, b);
}

}

#endif
