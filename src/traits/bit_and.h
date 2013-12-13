#ifndef TRAITOROUS_TRAITS_BITAND
#define TRAITOROUS_TRAITS_BITAND 1

#include <memory>

template<class S>
class BitAnd {
public:

  virtual std::shared_ptr<S> bit_and(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator&(std::shared_ptr<S> other) {
    return this->bit_and(other);
  }

};

#endif
