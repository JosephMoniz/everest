#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/md5.h>

namespace everest {

void Md5HashSpecification() {
  Describe("The Md5() function", []() {
    Describe("when called with the string 'lolwat'", []() {
      auto digest = Md5("lolwat");
      It("should return the hash 'c096629f2f8eaa7c3b428918893b39f8'", [&]() {
        AssertEquals(String("c096629f2f8eaa7c3b428918893b39f8"), Show(digest));
      });
    });
  });
};

}