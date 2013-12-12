#ifndef TRAITOROUS_TYPES_INT16
#define TRAITOROUS_TYPES_INT16 1

#include <cstdint>

#include "types/_basic_num.h"

class Int16 : public BasicNum<Int16, int16_t> {
public:

  Int16(int16_t n) : BasicNum(n) { }

};

#endif
