#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hmac/hmac_sha384.h>

namespace everest {

void HmacSha384HashSpecification() {
  Describe("The HmacSha384 functionality", []() {
    Describe("Contains the HmacSha384(String) function that", []() {
      Describe("when called with the key 'test' and mutable_string 'lolwat'", []() {
        auto digest = HmacSha384("test", "lolwat");
        It("should return the hash 'd3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5'", [&]() {
          AssertEquals(String("d3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5"), Show(digest));
        });
      });
    });
    Describe("Contains the HmacSha384() function that returns an HmacSha384Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = HmacSha384("test");
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash 'd3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5'", [&]() {
          AssertEquals(String("d3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = HmacSha384("test")
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash 'd3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5'", [&]() {
          AssertEquals(String("d3c5b9557e36d32017560927515839b2d9a405f80b20f9d0e56634ad7a287a7ca98dcd065c561de6ee73a0f3726cddc5"), Show(hash));
        });
      });
    });
  });
};

}