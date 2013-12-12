#ifndef TRAITOROUS_TRAITS_UNWRAPPABLE
#define TRAITOROUS_TRAITS_UNWRAPPABLE 1

#include <memory>

template<class S>
class Unwrappable {
public:

  virtual S get_value() = 0;

};

#endif
