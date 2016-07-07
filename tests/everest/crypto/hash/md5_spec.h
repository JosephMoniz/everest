#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/md5.h>

namespace everest {

void Md5HashSpecification() {
  Describe("The MD5 functionality", []() {
    Describe("contains the Md5(String) function that", []() {
      Describe("when called with the string 'lolwat'", []() {
        auto digest = Md5("lolwat");
        It("should return the hash 'c096629f2f8eaa7c3b428918893b39f8'", [&]() {
          AssertEquals(String("c096629f2f8eaa7c3b428918893b39f8"), Show(digest));
        });
      });
    });
    Describe("Contains the Md5() function that returns an Md5Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Md5();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash 'c096629f2f8eaa7c3b428918893b39f8'", [&]() {
          AssertEquals(String("c096629f2f8eaa7c3b428918893b39f8"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Md5()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash 'c096629f2f8eaa7c3b428918893b39f8'", [&]() {
          AssertEquals(String("c096629f2f8eaa7c3b428918893b39f8"), Show(hash));
        });
      });
    });
  });
};

}