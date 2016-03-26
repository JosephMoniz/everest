#ifndef TRAITOROUS_BOX_SPEC_H
#define TRAITOROUS_BOX_SPEC_H

#include <test/bdd.h>
#include <concurrency/conveyor.h>
#include <concurrency/box.h>

namespace traitorous {

void BoxSpecification() {
  Describe("A type Box", []() {
    Describe("that gets an item passed through it", []() {
      It("Should correctly convey an item through itself", []() {
        auto result = 0;
        auto box    = MakeBoxWithItem<bool, int>(42);
        box->Open(MakeConveyor<bool, int>(
          [](const bool& error) { },
          [&](const int& item)  { result = item; }
        ));
        return result == 42;
      });
      It("Should apply the transform when called with Map()", []() {
        auto result = 0;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto mapped = Map(Multiply(2), box);
        mapped->Open(MakeConveyor<bool, int>(
          [](const bool& error) { },
          [&](const int& item)  { result = item; }
        ));
        return result == 42;
      });
      It("Should correctly apply a succesfull FlatMap() transform", []() {
        auto result = 0;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto next   = FlatMap([](auto n) { return MakeBoxWithItem<bool, int>(n * 2); }, box);
        next->Open(MakeConveyor<bool, int>(
          [](const bool& error) { },
          [&](const int& item)  { result = item; }
        ));
        return result == 42;
      });
      It("Should correctly apply a failed FlatMap() transform", []() {
        auto result = false;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto next   = FlatMap([](auto n) { return MakeBoxWithError<bool, int>(true); }, box);
        next->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        return result;
      });
    });
    Describe("that gets an error passed through it", []() {
      It("Should correctly convey an error through itself", []() {
        auto result = false;
        auto box    = MakeBoxWithError<bool, int>(true);
        box->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [&](const int& item)   { /* Nothing to do here */ }
        ));
        return result;
      });
      It("Should pass the error on untouched when called with Map()", []() {
        auto result = false;
        auto box    = MakeBoxWithError<bool, int>(true);
        auto mapped = Map(Multiply(2), box);
        mapped->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        return result;
      });
      It("Should pass the error through untouched on a call to FlatMap()", []() {
        auto result = false;
        auto box    = MakeBoxWithError<bool, int>(true);
        auto next   = FlatMap([](auto n) { return MakeBoxWithError<bool, int>(false); }, box);
        next->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        return result;
      });
    });
  });
}

}

#endif
