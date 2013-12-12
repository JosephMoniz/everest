#ifndef TRAITOROUS_TRAITS_ORD
#define TRAITOROUS_TRAITS_ORD 1

#include <memory>

enum Ordering {
  LESS,
  EQUAL,
  GREATER
};

template<class S>
class Ord {
public:

  virtual Ordering cmp(std::shared_ptr<S> other) = 0;

};

#endif
