#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha224.h>

namespace everest {

void HmacSha224HashSpecification() {
  Describe("The HmacSha224() function", []() {
    Describe("when called with the key 'test' and string 'lolwat'", []() {
      auto digest = HmacSha224("test", "lolwat");
      It("should return the hash 'b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b'", [&]() {
        AssertEquals(String("b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b"), Show(digest));
      });
    });
  });
};

}