#ifndef TRAITOROUS_TYPES_INT32
#define TRAITOROUS_TYPES_INT32 1

#include <cstdint>

#include "types/_basic_num.h"

class Int32 : public BasicNum<Int32, int32_t> {
public:

  Int32(int32_t n) : BasicNum(n) { }

};

#endif
