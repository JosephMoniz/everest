#ifndef TRAITOROUS_TRAITS_BITOR
#define TRAITOROUS_TRAITS_BITOR 1

#include <memory>

template<class S>
class BitOr {
public:

  virtual std::shared_ptr<S> bit_or(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator|(std::shared_ptr<S> other) {
    return this->bit_or(other);
  }

};

#endif
