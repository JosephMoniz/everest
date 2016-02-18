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

//#include "local_nel_list_spec.h"


using namespace traitorous;

int main(int argc, char **argv) {
  // Type specifications
  //
  bool_specification();
  int8_specification();
  int16_specification();
  int32_specification();
  int64_specification();
  uint8_specification();
  uint16_specification();
  uint32_specification();
  string_specification();

  // Container specifications
  //
  LocalOptionSpecification();
  OptionSpecification();
  LocalArraySpecification();
  ArraySpecification();
  ListSpecification();


  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
}
