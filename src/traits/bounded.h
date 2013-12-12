#ifndef TRAITOROUS_TRAITS_BOUNDED
#define TRAITOROUS_TRAITS_BOUNDED 1

#include <memory>

template<class S>
class Bounded {
public:

  virtual std::shared_ptr<S> min_value() = 0;

  virtual std::shared_ptr<S> max_value() = 0;

};

#endif
