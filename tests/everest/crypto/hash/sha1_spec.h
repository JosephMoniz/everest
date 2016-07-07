#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha1.h>

namespace everest {

void Sha1HashSpecification() {
  Describe("The Sha1 functionality", []() {
    Describe("Contains the Sha1() function that", []() {
      Describe("when called with the string 'lolwat'", []() {
        auto digest = Sha1("lolwat");
        It("should return the hash '5b82762bc0f6615252dd3a794249473fab24b885'", [&]() {
          AssertEquals(String("5b82762bc0f6615252dd3a794249473fab24b885"), Show(digest));
        });
      });
    });
    Describe("Contains the Sha1() function that returns an Sha1Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Sha1();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '5b82762bc0f6615252dd3a794249473fab24b885'", [&]() {
          AssertEquals(String("5b82762bc0f6615252dd3a794249473fab24b885"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Sha1()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '5b82762bc0f6615252dd3a794249473fab24b885'", [&]() {
          AssertEquals(String("5b82762bc0f6615252dd3a794249473fab24b885"), Show(hash));
        });
      });
    });
  });
};

}