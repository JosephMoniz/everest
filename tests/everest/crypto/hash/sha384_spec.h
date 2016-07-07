#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha384.h>

namespace everest {

void Sha384HashSpecification() {
  Describe("The Sha384 functionality", []() {
    Describe("Contains the Sha384() function that", []() {
      Describe("when called with the string 'lolwat'", []() {
        auto digest = Sha384("lolwat");
        It("should return the hash '65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351'", [&]() {
          AssertEquals(String("65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351"), Show(digest));
        });
      });
    });
    Describe("Contains the Sha384() function that returns an Sha384Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Sha384();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351'", [&]() {
          AssertEquals(String("65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Sha384()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351'", [&]() {
          AssertEquals(String("65724edab8fbb76fffa6d01df1a6c576b381b0fe63e7e4c300d882db9a830ebc4976bb63a652097c35585bd3679f7351"), Show(hash));
        });
      });
    });
  });
};

}