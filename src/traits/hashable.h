#ifndef TRAITOROUS_TRAITS_HASHABLE
#define TRAITOROUS_TRAITS_HASHABLE 1

template <class T>
struct hashable {
  // int hash()
  static constexpr bool exists = false;
};

#endif
