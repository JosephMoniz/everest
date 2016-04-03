#pragma once

#include <everest/test/bdd.h>
#include <everest/concurrency/box.h>
#include <everest/traits/unlawful/multiply.h>

namespace everest {

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
        auto expected = 42;
        auto failure  = "Did not properly convey 42 on call to Open()";
        AssertEquals(failure, expected, result);
      });
      It("Should apply the transform when called with Map()", []() {
        auto result = 0;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto mapped = Map(Multiply(2), box);
        mapped->Open(MakeConveyor<bool, int>(
          [](const bool& error) { },
          [&](const int& item)  { result = item; }
        ));
        auto expected = 42;
        auto failure  = "Map(Multiply(2), Box(21)) did not produce Box(42)";
        AssertEquals(failure, expected, result);
      });
      It("Should correctly apply a successful FlatMap() transform", []() {
        auto result = 0;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto next   = FlatMap([](auto n) { return MakeBoxWithItem<bool, int>(n * 2); }, box);
        next->Open(MakeConveyor<bool, int>(
          [](const bool& error) { },
          [&](const int& item)  { result = item; }
        ));
        auto expected = 42;
        auto failure  = "FlatMap((n){ return Box(n*2) }) did not produce Box(42)";
        AssertEquals(failure, expected, result);
      });
      It("Should correctly apply a failed FlatMap() transform", []() {
        auto result = false;
        auto box    = MakeBoxWithItem<bool, int>(21);
        auto next   = FlatMap([](auto n) { return MakeBoxWithError<bool, int>(true); }, box);
        next->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        AssertTrue("FlatMap(Fn Box(Error)) did not produce Box(Error)", result);
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
        AssertTrue("Did not convey the error on call to Open()", result);
      });
      It("Should pass the error on untouched when called with Map()", []() {
        auto result = false;
        auto box    = MakeBoxWithError<bool, int>(true);
        auto mapped = Map(Multiply(2), box);
        mapped->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        AssertTrue("Did not convey the error on call to Open()", result);
      });
      It("Should pass the error through untouched on a call to FlatMap()", []() {
        auto result = false;
        auto box    = MakeBoxWithError<bool, int>(true);
        auto next   = FlatMap([](auto n) { return MakeBoxWithError<bool, int>(false); }, box);
        next->Open(MakeConveyor<bool, int>(
          [&](const bool& error) { result = error; },
          [](const int& item)    { }
        ));
        AssertTrue("Did not convey the error on call to Open()", result);
      });
    });
  });
}

}

