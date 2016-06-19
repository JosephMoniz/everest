#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha1.h>

namespace everest {

void HmacSha1HashSpecification() {
  Describe("The HmacSha1() function", []() {
    Describe("when called with the key 'test' and string 'lolwat'", []() {
      auto digest = HmacSha1("test", "lolwat");
      It("should return the hash '6253efcbc530d03405d4fded70bd7b6fdff439d7'", [&]() {
        AssertEquals(String("6253efcbc530d03405d4fded70bd7b6fdff439d7"), Show(digest));
      });
    });
  });
};

}