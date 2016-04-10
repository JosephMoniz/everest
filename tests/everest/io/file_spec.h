#pragma once

#include <everest/test/bdd.h>
#include <everest/io/file.h>

namespace everest {

void FileSpecification() {
  Describe("The file namespace", []() {
    Describe("has a method Exists()", []() {
      It("should return true when called with a file path that exists", []() {
        AssertTrue(file::Exists("./build/fixtures/existing_file.txt"));
      });
      It("should return false when called with a file path that doesn't exist", []() {
        AssertFalse(file::Exists("./build/fixtures/missing_file.txt"));
      });
    });
    Describe("Has a method Open()", []() {
      It("should return an Ok(File()) when called with a valid file");
    });
  });
}

}