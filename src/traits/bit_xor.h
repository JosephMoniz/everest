#ifndef TRAITOROUS_TRAITS_BITXOR
#define TRAITOROUS_TRAITS_BITXOR 1

#include <memory>

template<class S>
class BitXor {
public:

  virtual std::shared_ptr<S> bit_xor(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator|(std::shared_ptr<S> other) {
    return this->bit_xor(other);
  }

};

#endif
