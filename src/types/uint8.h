#ifndef TRAITOROUS_TYPES_UINT8
#define TRAITOROUS_TYPES_UINT8 1

#include <cstdint>

#include "types/_basic_num.h"

class UInt8 : public BasicNum<UInt8, uint8_t> {
public:

  UInt8(int n) : BasicNum(n) { }

};

#endif
