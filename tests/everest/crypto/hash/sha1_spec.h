#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha1.h>

namespace everest {

void Sha1HashSpecification() {
  Describe("The Sha1() function", []() {
    Describe("when called with the string 'lolwat'", []() {
      auto digest = Sha1("lolwat");
      It("should return the hash '5b82762bc0f6615252dd3a794249473fab24b885'", [&]() {
        AssertEquals(String("5b82762bc0f6615252dd3a794249473fab24b885"), Show(digest));
      });
    });
  });
};

}