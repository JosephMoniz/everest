#ifndef TRAITOROUS_TRAITS_REMAINDER
#define TRAITOROUS_TRAITS_REMAINDER 1

#include <memory>

template<class S>
class Remainder {
public:

  virtual std::shared_ptr<S> remainder(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator%(std::shared_ptr<S> other) {
    return this->remainder(other);
  }

};

#endif
