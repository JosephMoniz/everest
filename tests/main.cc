#include <everest/types/bool_spec.h>
#include <everest/types/int8_spec.h>
#include <everest/types/int16_spec.h>
#include <everest/types/int32_spec.h>
#include <everest/types/int64_spec.h>
#include <everest/types/uint8_spec.h>
#include <everest/types/uint16_spec.h>
#include <everest/types/uint32_spec.h>
#include <everest/types/uint64_spec.h>
#include <everest/types/string_spec.h>
#include <everest/containers/mutable/mutable_array_spec.h>
#include <everest/containers/mutable/mutable_shared_array_spec.h>
#include <everest/containers/array_spec.h>
#include <everest/containers/shared_array_spec.h>
#include <everest/containers/option_spec.h>
#include <everest/containers/shared_option_spec.h>
#include <everest/containers/list_spec.h>
#include <everest/containers/checked_spec.h>
#include <everest/containers/shared_checked_spec.h>
#include <everest/concurrency/box_spec.h>
#include <everest/containers/vector_spec.h>
#include <everest/containers/monoids/max_monoid_spec.h>
#include <everest/containers/monoids/min_monoid_spec.h>
#include <everest/io/file_spec.h>


using namespace everest;

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
  Uint64Specification();
  StringSpecification();

  // Mutable container specifications
  //
  MutableArraySpecification();
  SharedMutableArraySpecification();

  // Immutable container specifications
  //
  ArraySpecification();
  SharedArraySpecification();
  OptionSpecification();
  SharedOptionSpecification();
  ListSpecification();
  CheckedSpecification();
  SharedCheckSpecification();
  BoxSpecification();
  VectorSpecification();

  // Monoid specifications
  //
  MaxMonoidSpecification();
  MinMonoidSpecification();

  // IO Specifications
  FileSpecification();


  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
}
