#ifndef TRAITOROUS_LIST_SPEC_H
#define TRAITOROUS_LIST_SPEC_H

#include "test/bdd.h"

#include "containers/shared_ptr.h"
#include "containers/list.h"

namespace traitorous {

void list_specification() {
  describe("A list type", []() {
    it("should have a zero value of empty list", []() {
      return zero<list<int>>() == *cons<int>();
    });
    describe("that has no elements", []() {
      it("should call the correct case when called with match()", []() {
        return match(cons<int>(),
          []()                { return true; },
          [](auto x, auto xs) { return false; }
        );
      });
      it("should return false when called with contains()", []() {
        return !contains(42, cons<int>());
      });
      it("should return 0 when called with length()", []() {
        return length(cons<int>()) == 0;
      });
      it("should return true when called with is_empty()", []() {
        return is_empty(cons<int>());
      });
      it("should return true when called with equals() and an empty list", []() {
        return equals(cons<int>(), cons<int>());
      });
      it("should return false when called with equals and a non empty list", []() {
        return !equals(cons<int>(), cons(42));
      });
      it("should return true when called with == and an empty list", []() {
        return cons<int>() == cons<int>();
      });
      it("should return false when called with == and a non empty list", []() {
        return !(cons<int>() == cons(42));
      });
      it("should return false when called with != and empty list", []() {
        return !(cons<int>() != cons<int>());
      });
      it("should return true when called with != and a non empty list", []() {
        return (cons<int>() != cons(42));
      });
      it("should return hash 0 when called with hash()");
      it("should return the other list when called with add()", []() {
        return add(cons<int>(), make_list({1, 2, 3})) == make_list({1, 2, 3});
      });
    });
    describe("that has 3 elements", []() {
      it("should call the correct cases when passed through match()", []() {
        return match(make_list({1, 2, 3}),
          []() {
            return false;
          },
          [](auto x, auto xs) {
            if (x == 1) {
              return match(xs,
                []() {
                  return false;
                },
                [](auto y, auto ys) {
                  if (y == 2) {
                    return match(ys,
                      []() {
                        return false;
                      },
                      [](auto z, auto zs) {
                        if (z == 3) {
                          return match(zs,
                            []() {
                              return true;
                            },
                            [](auto _, auto __) {
                              return false;
                            }
                          );
                        } else {
                          return false;
                        }
                      }
                    );
                  } else {
                    return false;
                  }
                }
              );
            } else {
              return false;
            }
          }
        );
      });
      it("should return false when called with contains() and a different element", []() {
        return !contains(12, make_list({1, 2, 3}));
      });
      it("should return true when called with contains() and a matching element", []() {
        return contains(2, make_list({1, 2, 3}));
      });
      it("should return 3 when called with length() and a list of 3", []() {
        return length(make_list({1, 2, 3})) == 3;
      });
      it("should return false when called with is_empty() and a list of 3", []() {
        return !is_empty(make_list({1, 2, 3}));
      });
      it("should return true when called with equals() and a matching list", []() {
        return equals(make_list({1, 2, 3}), make_list({1, 2, 3}));
      });
      it("should return false when called with equals() and a non matching list", []() {
        return !equals(make_list({1, 2, 3}), make_list({4, 5, 6}));
      });
      it("should return true when called with == and a matching list", []() {
        return make_list({1, 2, 3}) == make_list({1, 2, 3});
      });
      it("should return false when called with == and a non matching list", []() {
        return !(make_list({1, 2, 3}) == make_list({4, 5, 6}));
      });
      it("should return false when called with != and a matching list", []() {
        return !(make_list({1, 2, 3}) != make_list({1, 2, 3}));
      });
      it("should return true when called with != and a non matching list", []() {
        return make_list({1, 2, 3}) != make_list({4, 5, 6});
      });
      it("should return the correct hash number when called with hash()");
      it("should return the merged lists when called with add()", []() {
        return add(make_list({1, 2, 3}), make_list({4, 5, 6})) == make_list({1, 2, 3, 4, 5, 6});
      });
    });
  });
}

}

#endif
