#include <everest/types/primitive/bool_spec.h>
#include <everest/types/primitive/int8_spec.h>
#include <everest/types/primitive/int16_spec.h>
#include <everest/types/primitive/int32_spec.h>
#include <everest/types/primitive/int64_spec.h>
#include <everest/types/primitive/uint8_spec.h>
#include <everest/types/primitive/uint16_spec.h>
#include <everest/types/primitive/uint32_spec.h>
#include <everest/types/primitive/uint64_spec.h>
#include <everest/types/string_spec.h>
#include <everest/containers/array_spec.h>
#include <everest/containers/option_spec.h>
#include <everest/containers/checked_spec.h>
#include <everest/containers/vector_spec.h>
#include <everest/containers/monoids/max_monoid_spec.h>
#include <everest/containers/monoids/min_monoid_spec.h>
#include <everest/io/file_spec.h>
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
#include <everest/types/bool_spec.h>
#include <everest/types/int8_spec.h>
#include <everest/types/int16_spec.h>
#include <everest/types/int32_spec.h>
#include <everest/types/int64_spec.h>
#include <everest/types/uint8_spec.h>
#include <everest/types/uint16_spec.h>
#include <everest/types/uint32_spec.h>
#include <everest/types/uint64_spec.h>
#include <everest/mutable_containers/mutable_array_spec.h>
#include <everest/mutable_containers/mutable_vector_spec.h>
#include <everest/mutable_containers/mutable_set_spec.h>
#include <everest/mutable_containers/mutable_map_spec.h>
#include <everest/mutable_containers/mutable_bit_set_spec.h>
#include <everest/mutable_containers/mutable_sorted_vector_set_spec.h>
#include <everest/mutable_containers/mutable_sorted_vector_map_spec.h>
#include <everest/mutable_crdt/counters/mutable_gcounter_spec.h>
#include <everest/mutable_crdt/counters/mutable_gacounter_spec.h>
#include <everest/mutable_crdt/counters/mutable_pncounter_spec.h>
#include <everest/mutable_crdt/counters/mutable_pnacounter_spec.h>
#include <everest/io/tcp_client_socket_spec.h>
#include <everest/io/tcp_client_server_spec.h>
#include <everest/mutable_containers/mutable_circular_buffer_spec.h>
#include <everest/concurrency/worker_pools/fixed_worker_pool.h>


using namespace everest;

int main(int argc, char **argv) {
  // Type specifications
  //
  PrimitiveBoolSpecification();
  PrimitiveInt8Specification();
  PrimitiveInt16Specification();
  PrimitiveInt32Specification();
  PrimitiveInt64Specification();
  PrimitiveUint8Specification();
  PrimitiveUint16Specification();
  PrimitiveUint32Specification();
  PrimitiveUint64Specification();
  BoolSpecification();
  Int8Specification();
  Int16Specification();
  Int32Specification();
  Int64Specification();
  UInt8Specification();
  UInt16Specification();
  UInt32Specification();
  UInt64Specification();
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

  // Mutable CRDT specifications
  //
  MutableGCounterSpecification();
  MutableGACounterSpecification();
  MutablePNCounterSpecification();
  MutablePNACounterSpecification();

  // IO Specifications
  //
  FileSpecification();
  TcpClientSocketSpecification();
  //TcpServerSpecification();

  // Mutable container specifications
  //
  MutableArraySpecification();
  MutableVectorSpecification();
  MutableSetSpecification();
  MutableMapSpecification();
  MutableBitSetSpecification();
  MutableSortedVectorSetSpecification();
  MutableSortedVectorMapSpecification();
  MutableCircularBufferSpecification();

  TcpServerSocket::Listen("8080").MatchWithMove(
    [](int error) {
      PrintLn("Hmmmm, some error");
    },
    [](TcpServerSocket&& server) {
      PrintLn("Listening on port 8080");
      auto channel = server.AcceptStream(1024);
      auto pool = FixedWorkerPool::Builder<TcpServerSocket::AcceptResult>()
        .SetStream(channel.GetStream())
        .SetWorkerCount(4)
        .SetRunnable([](TcpServerSocket::AcceptResult&& acceptResult) {
          acceptResult.MatchWithMove(
            [](int error) {
              Print("Something went wrong accepting the connection\n");
            },
            [](TcpClientSocket&& client) {
              Print("Yay, accepted socket connection\n");
              auto read = client.Read(1024 * 16);
              Print(Show(client._socket).Add("\n"));
              read.MatchWithMove(
                [](int error) {
                  Print("Something went wrong reading from the connection\n");
                },
                [](MutableVector<char>&& data) {
                  Print("Read from socket\n");
                }
              );
            }
          );
        })
        .Build();
      channel.Join();
      pool.Join();
    }
  );

  // Print and return the final test results
  //
  return PrintFinalResultsForTraitorousTest();
  
}
