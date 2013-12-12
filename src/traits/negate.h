#ifndef TRAITOROUS_TRAITS_NEGATE
#define TRAITOROUS_TRAITS_NEGATE 1

#include <memory>

template<class S>
class Negate {
public:

  virtual std::shared_ptr<S> negate() = 0;

};

#endif
