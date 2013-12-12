#ifndef TRAITOROUS_TRAITS_SUBTRACT
#define TRAITOROUS_TRAITS_SUBTRACT 1

#include <memory>

template<class S>
class Subtract {
public:

  virtual std::shared_ptr<S> subtract(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator-(std::shared_ptr<S> other) {
    return this->subtract(other);
  }

};

#endif
