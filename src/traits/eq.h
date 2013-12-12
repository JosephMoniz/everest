#ifndef TRAITOROUS_TRAITS_EQ
#define TRAITOROUS_TRAITS_EQ 1

#include <memory>

template<class S>
class Eq {
public:

  virtual bool equals(std::shared_ptr<S> other) = 0;

  virtual bool operator==(std::shared_ptr<S> other) {
    return this->equals(other);
  }

};

#endif
