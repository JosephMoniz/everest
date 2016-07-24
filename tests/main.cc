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
#include <everest/containers/mutable/mutable_vector_spec.h>
#include <everest/containers/array_spec.h>
#include <everest/containers/option_spec.h>
#include <everest/containers/checked_spec.h>
//#include <everest/concurrency/box_spec.h>
#include <everest/containers/vector_spec.h>
#include <everest/containers/monoids/max_monoid_spec.h>
#include <everest/containers/monoids/min_monoid_spec.h>
#include <everest/io/file_spec.h>
#include <everest/containers/mutable/mutable_set_spec.h>
#include <everest/containers/mutable/mutable_map_spec.h>
#include <everest/containers/set_spec.h.h>
#include <everest/crypto/hash/md5_spec.h>
#include <everest/crypto/hash/sha1_spec.h>
#include <everest/crypto/hash/sha256_spec.h>
#include <everest/crypto/hash/sha512_spec.h>
#include <everest/crypto/hmac/hmac_md5_spec.h>
#include <everest/crypto/hmac/hmac_sha1_spec.h>
#include <everest/crypto/hmac/hmac_sha256_spec.h>
#include <everest/crypto/hmac/hmac_sha512_spec.h>
#include <everest/crypto/hash/sha224_spec.h>
#include <everest/crypto/hash/sha384_spec.h>
#include <everest/crypto/hmac/hmac_sha224_spec.h>
#include <everest/crypto/hmac/hmac_sha384_spec.h>
#include <everest/containers/mutable/mutable_bit_set_spec.h>
#include <everest/containers/mutable/mutable_sorted_vector_set_spec.h>


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

  // Immutable container specifications
  //
  ArraySpecification();
  OptionSpecification();
  CheckedSpecification();
  //BoxSpecification();
  VectorSpecification();
  SetSpecification();

  // Monoid specifications
  //
  MaxMonoidSpecification();
  MinMonoidSpecification();

  // IO Specifications
  //
  FileSpecification();

  // Hash Specifications
  //
  Md5HashSpecification();
  Sha1HashSpecification();
  Sha224HashSpecification();
  Sha256HashSpecification();
  Sha384HashSpecification();
  Sha512HashSpecification();

  // Hmac Specifications
  HmacMd5HashSpecification();
  HmacSha1HashSpecification();
  HmacSha224HashSpecification();
  HmacSha256HashSpecification();
  HmacSha384HashSpecification();
  HmacSha512HashSpecification();

  // Mutable container specifications
  //
  MutableArraySpecification();
  MutableVectorSpecification();
  MutableSetSpecification();
  MutableMapSpecification();
  MutableBitSetSpecification();
  MutableSortedVectorSetSpecification();

  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
}
