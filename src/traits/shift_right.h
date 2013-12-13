#ifndef TRAITOROUS_TRAITS_SHIFTRIGHT
#define TRAITOROUS_TRAITS_SHIFTRIGHT 1

#include <memory>

template<class S>
class ShiftRight {
public:

  virtual std::shared_ptr<S> shift_right(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator>>(std::shared_ptr<S> other) {
    return this->shift_right(other);
  }

};

#endif
