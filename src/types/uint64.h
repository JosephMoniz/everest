#ifndef TRAITOROUS_TYPES_UINT64
#define TRAITOROUS_TYPES_UINT64 1

#include <cstdint>

#include "types/_basic_num.h"

class UInt64 : public BasicNum<UInt64, uint64_t> {
public:

  UInt64(uint64_t n) : BasicNum(n) { }

};

#endif
