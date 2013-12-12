#ifndef TRAITOROUS_TYPES_INT64
#define TRAITOROUS_TYPES_INT64 1

#include <cstdint>

#include "types/_basic_num.h"

class Int64 : public BasicNum<Int64, int64_t> {
public:

  Int64(int64_t n) : BasicNum(n) { }

};

#endif
