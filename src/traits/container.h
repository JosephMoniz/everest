#ifndef TRAITOROUS_TRAITS_CONTAINER
#define TRAITOROUS_TRAITS_CONTAINER 1

#include <memory>

#include "types/uint.h"

class Container {
public:

  virtual std::shared_ptr<UInt> length() = 0;

  virtual bool is_empty() = 0;

};

#endif
