#ifndef TRAITOROUS_TYPES_UINT32
#define TRAITOROUS_TYPES_UINT32 1

#include <cstdint>

#include "types/_basic_num.h"

class UInt32 : public BasicNum<UInt32, uint32_t> {
public:

  UInt32(uint32_t n) : BasicNum(n) { }

};

#endif
