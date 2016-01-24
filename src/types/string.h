#ifndef TRAITOROUS_TYPES_STRING
#define TRAITOROUS_TYPES_STRING 1

#include <string>

#include "traits/unlawful/container.h"
#include "traits/unlawful/eq.h"
#include "traits/unlawful/zero.h"
#include "traits/lawful/semigroup.h"
#include "traits/lawful/monoid.h"
#include "traits/unlawful/ord.h"
#include "traits/unlawful/show.h"

namespace traitorous {

enum string_type {
  BASE_STRING,
  CONCAT_STRING,
  SLICED_STRING
};

class string {
public:

  virtual string_type get_type() = 0;

};

}

#endif
