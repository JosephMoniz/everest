#ifndef TRAITOROUS_TRAITS_SHIFTLEFT
#define TRAITOROUS_TRAITS_SHIFTLEFT 1

#include <memory>

template<class S>
class ShiftLeft {
public:

  virtual std::shared_ptr<S> shift_left(std::shared_ptr<S> other) = 0;

  virtual std::shared_ptr<S> operator<<(std::shared_ptr<S> other) {
    return this->shift_left(other);
  }

};

#endif
