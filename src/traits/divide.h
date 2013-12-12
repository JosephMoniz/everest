#ifndef TRAITOROUS_TRAITS_DIVIDE
#define TRAITOROUS_TRAITS_DIVIDE 1

#include <memory>

template<class S>
class Divide {
public:

  virtual std::shared_ptr<S> divide(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator/(std::shared_ptr<S> other) {
    return this->divide(other);
  }

};

#endif
