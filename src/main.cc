#include <traitorous_specs/types/bool_spec.h>
#include <traitorous_specs/types/int8_spec.h>
#include <traitorous_specs/types/int16_spec.h>
#include <traitorous_specs/types/int32_spec.h>
#include <traitorous_specs/types/int64_spec.h>
#include <traitorous_specs/types/uint8_spec.h>
#include <traitorous_specs/types/uint16_spec.h>
#include <traitorous_specs/types/uint32_spec.h>
#include <traitorous_specs/types/string_spec.h>
#include <traitorous_specs/containers/local_option_spec.h>
#include <traitorous_specs/containers/option_spec.h>
#include <traitorous_specs/containers/array_spec.h>
#include <traitorous_specs/containers/local_array_spec.h>
#include <traitorous_specs/containers/list_spec.h>
#include <traitorous_specs/containers/local_checked_spec.h>
#include <traitorous_specs/containers/checked_spec.h>
#include <traitorous_specs/concurrency/box_spec.h>

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
  LocalOptionSpecification();
  OptionSpecification();
  LocalArraySpecification();
  ArraySpecification();
  ListSpecification();
  LocalCheckedSpecification();
  CheckedSpecification();
  BoxSpecification();


  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
}
