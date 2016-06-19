#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha256.h>

namespace everest {

void Sha256HashSpecification() {
  Describe("The Sha256() function", []() {
    Describe("when called with the string 'lolwat'", []() {
      auto digest = Sha256("lolwat");
      It("should return the hash '9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680'", [&]() {
        AssertEquals(String("9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680"), Show(digest));
      });
    });
  });
};

}