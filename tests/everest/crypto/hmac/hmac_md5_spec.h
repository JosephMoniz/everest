#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_md5.h>

namespace everest {

void HmacMd5HashSpecification() {
  Describe("The HmacMd5() function", []() {
    Describe("when called with the key 'test' and string 'lolwat'", []() {
      auto digest = HmacMd5("test", "lolwat");
      It("should return the hash '197fa8a01fac6bdfa08b3d55b6121211'", [&]() {
        AssertEquals(String("197fa8a01fac6bdfa08b3d55b6121211"), Show(digest));
      });
    });
  });
};

}