#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha256.h>

namespace everest {

void HmacSha256HashSpecification() {
  Describe("The HmacSha256 functionality", []() {
    Describe("Contains a HmacSha256(String) function that", []() {
      Describe("when called with the key 'test' and mutable_string 'lolwat'", []() {
        auto digest = HmacSha256("test", "lolwat");
        It("should return the hash '43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4'", [&]() {
          AssertEquals(String("43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacSha256() function that returns an HmacSha256Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacSha256("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4'", [&]() {
          AssertEquals(String("43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacSha256("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4'", [&]() {
          AssertEquals(String("43a8952b8756b575c42ddd5e8588c66d4b5f0b09298e6e9ebae1759228b5a3a4"), Show(hash));
        });
      });
    });
  });
};

}