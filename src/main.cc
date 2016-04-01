#include <everest/specs/types/bool_spec.h>
#include <everest/specs/types/int8_spec.h>
#include <everest/specs/types/int16_spec.h>
#include <everest/specs/types/int32_spec.h>
#include <everest/specs/types/int64_spec.h>
#include <everest/specs/types/uint8_spec.h>
#include <everest/specs/types/uint16_spec.h>
#include <everest/specs/types/uint32_spec.h>
#include <everest/specs/types/string_spec.h>
#include <everest/specs/containers/option_spec.h>
#include <everest/specs/containers/shared_option_spec.h>
#include <everest/specs/containers/array_spec.h>
#include <everest/specs/containers/shared_array_spec.h>
#include <everest/specs/containers/list_spec.h>
#include <everest/specs/containers/checked_spec.h>
#include <everest/specs/containers/shared_checked_spec.h>
#include <everest/specs/concurrency/box_spec.h>

using namespace traitorous;

int main(int argc, char **argv) {
  // Type specifications
  //
  BoolSpecification();
  Int8Specification();
  Int16Specification();
  Int32Specification();
  Int64Specification();
  Uint8Specification();
  Uint16Specification();
  Uint32Specification();
  StringSpecification();

  // Container specifications
  //
  OptionSpecification();
  SharedOptionSpecification();
  ArraySpecification();
  SharedArraySpecification();
  ListSpecification();
  CheckedSpecification();
  SharedCheckSpecification();
  BoxSpecification();


  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
}
