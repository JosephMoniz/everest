#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_md5.h>

namespace everest {

void HmacMd5HashSpecification() {
  Describe("The HmacMd5 functionality", []() {
    Describe("Contains the HmacMd5(String) function that", []() {
      Describe("when called with the key 'test' and mutable_string 'lolwat'", []() {
        auto digest = HmacMd5("test", "lolwat");
        It("should return the hash '197fa8a01fac6bdfa08b3d55b6121211'", [&]() {
          AssertEquals(String("197fa8a01fac6bdfa08b3d55b6121211"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacMd5() function that returns an HmacMd5Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacMd5("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '197fa8a01fac6bdfa08b3d55b6121211'", [&]() {
          AssertEquals(String("197fa8a01fac6bdfa08b3d55b6121211"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacMd5("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '197fa8a01fac6bdfa08b3d55b6121211'", [&]() {
          AssertEquals(String("197fa8a01fac6bdfa08b3d55b6121211"), Show(hash));
        });
      });
    });
  });
};

}