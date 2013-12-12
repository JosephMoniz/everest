#ifndef TRAITOROUS_TYPES_INT8
#define TRAITOROUS_TYPES_INT8 1

#include <cstdint>

#include "types/_basic_num.h"

class Int8 : public BasicNum<Int8, int8_t> {
public:

  Int8(int8_t n) : BasicNum(n) { }

};

#endif
