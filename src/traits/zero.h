#ifndef TRAITOROUS_TRAITS_ZERO
#define TRAITOROUS_TRAITS_ZERO 1

#include <memory>

template<class S>
class Zero {
public:

  virtual std::shared_ptr<S> zero() = 0;

};

#endif
