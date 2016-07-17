#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha256.h>

namespace everest {

void Sha256HashSpecification() {
  Describe("The Sha256 functionality", []() {
    Describe("Contains the Sha256(String) function that", []() {
      Describe("when called with the string 'lolwat'", []() {
        auto digest = Sha256("lolwat");
        It("should return the hash '9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680'", [&]() {
          AssertEquals(String("9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680"), Show(digest));
        });
      });
    });
    Describe("Contains the Sha256() function that returns an Sha256Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Sha256();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680'", [&]() {
          AssertEquals(String("9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Sha256()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680'", [&]() {
          AssertEquals(String("9d4739ea8d2a9d26db59bf127163dc8a598b68df2cc6cd356d9cca8f77d72680"), Show(hash));
        });
      });
    });
  });
};

}