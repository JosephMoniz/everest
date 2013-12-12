#ifndef TRAITOROUS_TRAITS_MULTIPLY
#define TRAITOROUS_TRAITS_MULTIPLY 1

#include <memory>

template<class S>
class Multiply {
public:

  virtual std::shared_ptr<S> multiply(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator*(std::shared_ptr<S> other) {
    return this->multiply(other);
  }

};

#endif
