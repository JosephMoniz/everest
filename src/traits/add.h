#ifndef TRAITOROUS_TRAITS_ADD
#define TRAITOROUS_TRAITS_ADD 1

#include <memory>

template<class S>
class Add {
public:

  virtual std::shared_ptr<S> add(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator+(std::shared_ptr<S> other) {
    return this->add(other);
  }

};

#endif
