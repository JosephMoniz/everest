#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha256.h>

namespace everest {

void HmacSha256HashSpecification() {
  Describe("The HmacSha256() function", []() {
    Describe("when called with the key 'test' and string 'lolwat'", []() {
      auto digest = HmacSha256("test", "lolwat");
      It("should return the hash '43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4'", [&]() {
        AssertEquals(String("43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4"), Show(digest));
      });
    });
  });
};

}