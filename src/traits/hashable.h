#ifndef TRAITOROUS_TRAITS_HASHABLE
#define TRAITOROUS_TRAITS_HASHABLE 1

#include <memory>

#include "types/uint32.h"

class Hashable {
public:

  virtual std::shared_ptr<UInt32> hash() = 0;

};

#endif
