#pragma once

#include <everest/test/bdd.h>
#include <everest/io/file.h>
#include <everest/io/file/stat.h>
#include <everest/io/memory_mapped_file.h>

namespace everest {

void FileSpecification() {
  Describe("The file namespace", []() {
    Describe("has a method Exists()", []() {
      It("should return true when called with a file path that exists", []() {
        AssertTrue(file::Stat::Of("./build/fixtures/existing_file.txt").IsOk());
      });
      It("should return false when called with a file path that doesn't exist", []() {
        AssertFalse(file::Stat::Of("./build/fixtures/missing_file.txt").IsOk());
      });
    });
    Describe("has a method Open()", []() {
      It("should return an Ok(File()) when called with a valid file", []() {
        auto file = File::Open("./build/fixtures/existing_file.txt");
        AssertTrue("File::Open() did not succeed", file.IsOk());
      });
    });
    Describe("has a method Touch()", []() {
      It("should create a file when called with a non existing file name", []() {
        auto path   = "./build/fixtures/newly_created_file.txt";
        auto result = File::Touch(path);
        auto exists = file::Stat::Of(path).IsOk();
        auto file   = File::Open(path);
        AssertTrue("Failed creating new file", result);
        AssertTrue("File that was created doesn't exist", exists);
        AssertTrue("Can't open newly created file", file.IsOk());
      });
    });
    Describe("has a method Unlink()", []() {
      It("should delete the file passed to it", []() {
        auto path    = "./build/fixtures/unlinkable_file.txt";
        auto existed = file::Stat::Of(path).IsOk();
        auto result  = File::Unlink(path);
        auto exists  = file::Stat::Of(path).IsOk();
        AssertTrue("File never existed in the first place", existed);
        AssertTrue("Failed deleting file", result);
        AssertFalse("Did not actually delete file", exists);
      });
    });
    Describe("has memory mapped files", []() {
      It("Should be able to mmap it", []() {
        auto path     = "./build/fixtures/mappable_file.txt";
        auto file     = File::Open(path);
        auto mapped   = MemoryMappedFile::of(file.GetMovable());
        auto map      = mapped.GetMovable();
        auto expected = "file content here";
        auto pointer  = (char *) map.Pointer();
        for (size_t i = 0; i < map.Size(); i++) {
          AssertEquals("Unexpected file content", expected[i], pointer[i]);
        }
      });
    });
  });
}

}
