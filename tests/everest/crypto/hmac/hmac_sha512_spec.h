#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha512.h>

namespace everest {

void HmacSha512HashSpecification() {
  Describe("The HmacSha512 functionality", []() {
    Describe("Contains the HmacSha512(String) function that", []() {
      Describe("when called with the key 'test' and string 'lolwat'", []() {
        auto digest = HmacSha512("test", "lolwat");
        It("should return the hash '07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf'", [&]() {
          AssertEquals(String("07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacSha512() function that returns an HmacSha512Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacSha512("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf'", [&]() {
          AssertEquals(String("07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacSha512("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf'", [&]() {
          AssertEquals(String("07f1cf282ee66311e156bd45651fea33d22ed54fe14b4b201f9a275f2582a49ca3fcd5fa2fb48c8bff4f5eb519a8713cdfe57e738d743a44389f0c01de5267cf"), Show(hash));
        });
      });
    });
  });
};

}