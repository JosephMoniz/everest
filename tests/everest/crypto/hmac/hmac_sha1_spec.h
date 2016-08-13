#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha1.h>

namespace everest {

void HmacSha1HashSpecification() {
  Describe("The HmacSha1 functionality", []() {
    Describe("Contains the HmacSha1(String) function that", []() {
      Describe("when called with the key 'test' and mutable_string 'lolwat'", []() {
        auto digest = HmacSha1("test", "lolwat");
        It("should return the hash '6253efcbc530d03405d4fded70bd7b6fdff439d7'", [&]() {
          AssertEquals(String("6253efcbc530d03405d4fded70bd7b6fdff439d7"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacSha1() function that returns an HmacSha1Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacSha1("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '6253efcbc530d03405d4fded70bd7b6fdff439d7'", [&]() {
          AssertEquals(String("6253efcbc530d03405d4fded70bd7b6fdff439d7"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacSha1("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '6253efcbc530d03405d4fded70bd7b6fdff439d7'", [&]() {
          AssertEquals(String("6253efcbc530d03405d4fded70bd7b6fdff439d7"), Show(hash));
        });
      });
    });
  });
};

}