#pragma once

#include <sys/mman.h>
#include <everest/io/file.h>
#include <everest/io/file/stat.h>
#include <everest/containers/checked.h>
#include <everest/traits/unlawful/pointable.h>

namespace everest {

template<class E, class S>
class Checked;

class MemoryMappedFile final {

  friend class Pointable<MemoryMappedFile>;

  File _file;

  size_t _size;

  void* _pointer;

  MemoryMappedFile(File&& file, size_t size, void* pointer) noexcept : _file(std::move(file)),
                                                                       _size(size),
                                                                       _pointer(pointer) { }

public:

  MemoryMappedFile(const MemoryMappedFile& file) = delete;

  MemoryMappedFile(MemoryMappedFile&& other) noexcept : _file(std::move(other._file)),
                                                        _size(other._size),
                                                        _pointer(other._pointer)
  {
    other._pointer = nullptr;
  }

  ~MemoryMappedFile() noexcept {
    if (_pointer != nullptr) {
      munmap(_pointer, _size);
    }
  }

  static Checked<int, MemoryMappedFile> Of(File&& file) noexcept {
    auto stat = file::Stat::Of(file);
    if (stat.IsOk()) {
      auto size    = (size_t) stat.Get().Size();
      auto options = PROT_READ | PROT_WRITE;
      auto flags   = MAP_FILE | MAP_SHARED;
      auto pointer = mmap(nullptr, size, options, flags, file.Descriptor(), 0);
      if (pointer != MAP_FAILED) {
        return Checked<int, MemoryMappedFile>::Ok(MemoryMappedFile(std::move(file), size, pointer));
      } else {
        return Checked<int, MemoryMappedFile>::Error(errno);
      }
    } else {
      return Checked<int, MemoryMappedFile>::Error(stat.GetError());
    }
  }

  static Checked<int, MemoryMappedFile> Of(const char* filePath) noexcept {
    auto file = File::Open(filePath);
    return file.IsOk()
      ? MemoryMappedFile::Of(file.GetMovable())
      : Checked<int, MemoryMappedFile>::Error(file.GetError());
  };

  size_t Size() const noexcept {
    return _size;
  }

};

template <>
class Pointable<MemoryMappedFile> final {
public:

  static constexpr bool exists = true;

  static const void* Pointer(const MemoryMappedFile& file) noexcept {
    return (const void*) file._pointer;
  }

};

}
