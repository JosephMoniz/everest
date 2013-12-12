#ifndef TRAITOROUS_TYPES_UINT
#define TRAITOROUS_TYPES_UINT 1

#include <cstdint>

#include "types/_basic_num.h"

class UInt : public BasicNum<UInt, unsigned int> {
public:

  UInt(unsigned int n) : BasicNum(n) { }

};

#endif
