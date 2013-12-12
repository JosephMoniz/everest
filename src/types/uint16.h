#ifndef TRAITOROUS_TYPES_UINT16
#define TRAITOROUS_TYPES_UINT16 1

#include <cstdint>

#include "types/_basic_num.h"

class UInt16 : public BasicNum<UInt16, uint16_t> {
public:

  UInt16(uint16_t n) : BasicNum(n) { }

};

#endif
