#pragma once

#include <everest/test/bdd.h>
#include <everest/crypto/hash/sha224.h>

namespace everest {

void Sha224HashSpecification() {
  Describe("The Sha224 functionality", []() {
    Describe("Contains the Sha224() function that", []() {
      Describe("when called with the string 'lolwat'", []() {
        auto digest = Sha224("lolwat");
        It("should return the hash '41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d'", [&]() {
          AssertEquals(String("41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d"), Show(digest));
        });
      });
    });
    Describe("Contains the Sha224() function that returns an Sha224Sink that", []() {
      Describe("When pushing 'lol' and then 'what' through it with the functional interface", []() {
        auto sink = Sha224();
        PushThrough("lol", sink);
        PushThrough("wat", sink);
        It("should return the hash '41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d'", [&]() {
          AssertEquals(String("41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d"), Show(CloseSink(sink)));
        });
      });
      Describe("When pushing 'lol' and then 'what' through it with the OO interface", []() {
        auto hash = Sha224()
          .PushThrough("lol")
          .PushThrough("wat")
          .Hash();
        It("should return the hash '41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d'", [&]() {
          AssertEquals(String("41b353d6b74874890574152d326da7202c7a3354d014081a85c1363d"), Show(hash));
        });
      });
    });
  });
};

}