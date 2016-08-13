#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha512.h>

namespace everest {

void Sha512HashSpecification() {
  Describe("The Sha512 functionality", []() {
    Describe("Contains the Sha512(String) function that", []() {
      Describe("when called with the mutable_string 'lolwat'", []() {
        auto digest = Sha512("lolwat");
        It("should return the hash '3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2'", [&]() {
          AssertEquals(String("3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2"), Show(digest));
        });
      });
    });
    Describe("Contains the Sha512() function that returns an Sha512Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Sha512();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2'", [&]() {
          AssertEquals(String("3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Sha512()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2'", [&]() {
          AssertEquals(String("3882be8f487cf4973cbcb7a40a0ba3aa634ecf783bbe361a52c8d874a61b4e6f7898193293e1d1983379bd258e20212b60ec77f2104b279820cc2390878c67a2"), Show(hash));
        });
      });
    });
  });
};

}