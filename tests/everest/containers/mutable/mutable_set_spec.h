#pragma once

#include <everest/test/bdd.h>
#include <everest/containers/mutable/mutable_vector.h>
#include <everest/functions/identity.h>
#include <everest/traits/unlawful/multiply.h>
#include <everest/containers/mutable/mutable_set.h>
#include <everest/traits/unlawful/mutable/mutable_remove.h>

namespace everest {

void MutableSetSpecification() {
  Describe("A MutableSet type", []() {
    Describe("of value {1, 2, 3, 4}", []() {
      auto subject = MutableSet<int>();
      AddInPlace(1, subject);
      AddInPlace(2, subject);
      AddInPlace(3, subject);
      AddInPlace(4, subject);
      It("Should return false when called with Contains(0)", [&]() {
        AssertFalse(Contains(0, subject));
      });
      It("Should return true when called with Contains(1)", [&]() {
        AssertTrue(Contains(1, subject));
      });
      It("Should return true when called with Contains(2)", [&]() {
        AssertTrue(Contains(2, subject));
      });
      It("Should return true when called with Contains(3)", [&]() {
        AssertTrue(Contains(3, subject));
      });
      It("Should return true when called with Contains(4)", [&]() {
        AssertTrue(Contains(4, subject));
      });
      It("Should return false when called with Contains(5)", [&]() {
        AssertFalse(Contains(5, subject));
      });
      Describe("and we call Remove(1)", [&]() {
        RemoveInPlace(1, subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return true when called with Contains(2)", [&]() {
          AssertTrue(Contains(2, subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(2)", [&]() {
        RemoveInPlace(2, subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return true when called with Contains(3)", [&]() {
          AssertTrue(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(3)", [&]() {
        RemoveInPlace(3, subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(3, subject));
        });
        It("Should return true when called with Contains(4)", [&]() {
          AssertTrue(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
      Describe("and we call Remove(4)", [&]() {
        RemoveInPlace(4, subject);
        It("Should return false when called with Contains(0)", [&]() {
          AssertFalse(Contains(0, subject));
        });
        It("Should return false when called with Contains(1)", [&]() {
          AssertFalse(Contains(1, subject));
        });
        It("Should return false when called with Contains(2)", [&]() {
          AssertFalse(Contains(2, subject));
        });
        It("Should return false when called with Contains(3)", [&]() {
          AssertFalse(Contains(3, subject));
        });
        It("Should return false when called with Contains(4)", [&]() {
          AssertFalse(Contains(4, subject));
        });
        It("Should return false when called with Contains(5)", [&]() {
          AssertFalse(Contains(5, subject));
        });
      });
    });
  });
}

}