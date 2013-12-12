#ifndef TRAITOROUS_TYPES_INT
#define TRAITOROUS_TYPES_INT 1

#include "types/_basic_num.h"

class Int : public BasicNum<Int, int> {
public:

  Int(int n) : BasicNum(n) { }

};

#endif
