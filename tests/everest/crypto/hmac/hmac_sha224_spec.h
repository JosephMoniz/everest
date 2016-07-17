#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha224.h>

namespace everest {

void HmacSha224HashSpecification() {
  Describe("The HmacSha224 functionality", []() {
    Describe("Contains the HmacSha224(String) function that", []() {
      Describe("when called with the key 'test' and string 'lolwat'", []() {
        auto digest = HmacSha224("test", "lolwat");
        It("should return the hash 'b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b'", [&]() {
          AssertEquals(String("b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacSha224() function that returns an HmacSha224Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacSha224("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash 'b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b'", [&]() {
          AssertEquals(String("b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacSha224("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash 'b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b'", [&]() {
          AssertEquals(String("b83250da88c2a142383c491887406fb754700bdcef89130b9fcc243b"), Show(hash));
        });
      });
    });
  });
};

}