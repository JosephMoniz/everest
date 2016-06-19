#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha512.h>

namespace everest {

void Sha512HashSpecification() {
  Describe("The Sha512() function", []() {
    Describe("when called with the string 'lolwat'", []() {
      auto digest = Sha512("lolwat");
      It("should return the hash '3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2'", [&]() {
        AssertEquals(String("3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2"), Show(digest));
      });
    });
  });
};

}