#pragma once

#include <everest/test/bdd.h>
#include <everest/mutable_containers/mutable_array.h>
#include <everest/mutable_containers/array/all_traits.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/traits/unlawful/ord/ordering/all_traits.h>
#include <everest/types/size/all_traits.h>
#include <everest/mutable_containers/mutable_circular_buffer.h>

namespace everest {

void MutableCircularBufferSpecification() {
  Describe("A MutableCircularBuffer type of size 3", []() {
    MutableCircularBuffer<int> buffer(3);
    Describe("and we enqueue a first element to it", [&]() {
      auto result = buffer.Enqueue(1);
      It("should return true", [&]() {
        AssertTrue(result);
      });
      It("should return 1 for the current size", [&]() {
        AssertEquals((size_t)1, buffer.Length());
      });
    });
    Describe("and we enqueue a second element to it", [&]() {
      auto result = buffer.Enqueue(2);
      It("should return true", [&]() {
        AssertTrue(result);
      });
      It("should return 2 for the current size", [&]() {
        AssertEquals((size_t)2, buffer.Length());
      });
    });
    Describe("and we enqueue a third element to it", [&]() {
      auto result = buffer.Enqueue(3);
      It("should return true", [&]() {
        AssertTrue(result);
      });
      It("should return 3 for the current size", [&]() {
        AssertEquals((size_t)3, buffer.Length());
      });
    });
    Describe("and we enqueue a fourth element to it", [&]() {
      auto result = buffer.Enqueue(4);
      It("should return false", [&]() {
        AssertFalse(result);
      });
      It("should return 3 for the current size", [&]() {
        AssertEquals((size_t)3, buffer.Length());
      });
    });
    Describe("and we dequeue the first element", [&]() {
      auto result = buffer.Dequeue();
      It("should return a pointer to the first element", [&]() {
        AssertEquals(1, *result);
      });
      It("should return 2 for the current size", [&]() {
        AssertEquals((size_t)2, buffer.Length());
      });
    });
    Describe("and we dequeue the second element", [&]() {
      auto result = buffer.Dequeue();
      It("should return a pointer to the second element", [&]() {
        AssertEquals(2, *result);
      });
      It("should return 1 for the current size", [&]() {
        AssertEquals((size_t)1, buffer.Length());
      });
    });
    Describe("and we enqueue a fourth element", [&]() {
      auto result = buffer.Enqueue(4);
      It("should return true", [&]() {
        AssertTrue(result);
      });
      It("should return 2 for the current size", [&]() {
        AssertEquals((size_t)2, buffer.Length());
      });
    });
    Describe("and we enqueue a fifth element", [&]() {
      auto result = buffer.Enqueue(5);
      It("should return true", [&]() {
        AssertTrue(result);
      });
      It("should return 3 for the current size", [&]() {
        AssertEquals((size_t)3, buffer.Length());
      });
    });
    Describe("and we dequeue the third element", [&]() {
      auto result = buffer.Dequeue();
      It("should return a pointer to the third element", [&]() {
        AssertEquals(3, *result);
      });
      It("should return 2 for the current size", [&]() {
        AssertEquals((size_t)2, buffer.Length());
      });
    });
    Describe("and we dequeue the fourth element", [&]() {
      auto result = buffer.Dequeue();
      It("should return a pointer to the fourth element", [&]() {
        AssertEquals(4, *result);
      });
      It("should return 1 for the current size", [&]() {
        AssertEquals((size_t)1, buffer.Length());
      });
    });
    Describe("and we dequeue the fifth element", [&]() {
      auto result = buffer.Dequeue();
      It("should return a pointer to the fifth element", [&]() {
        AssertEquals(5, *result);
      });
      It("should return 0 for the current size", [&]() {
        AssertEquals((size_t)0, buffer.Length());
      });
    });
    Describe("and we dequeue an empty buffer", [&]() {
      auto result = buffer.Dequeue();
      It("should return a nullptr", [&]() {
        AssertEquals((int*)nullptr, result);
      });
    });
  });
}

}
