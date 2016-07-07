#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha384.h>

namespace everest {

void HmacSha384HashSpecification() {
  Describe("The HmacSha384() function", []() {
    Describe("when called with the key 'test' and string 'lolwat'", []() {
      auto digest = HmacSha384("test", "lolwat");
      It("should return the hash 'd3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5'", [&]() {
        AssertEquals(String("d3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5"), Show(digest));
      });
    });
  });
};

}