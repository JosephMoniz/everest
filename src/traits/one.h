#ifndef TRAITOROUS_TRAITS_ONE
#define TRAITOROUS_TRAITS_ONE 1

#include <memory>

template<class S>
class One {
public:

  virtual std::shared_ptr<S> one() = 0;

};

#endif
