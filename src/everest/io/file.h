#pragma once

#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <everest/types/string.h>
#include <everest/containers/option.h>
#include <everest/containers/checked.h>
#include <everest/io/file/file_open_error.h>

namespace everest {

class File final {
public:

  const int descriptor;

  const int flags;

  File(int descriptor, int flags) noexcept : descriptor(descriptor), flags(flags) { }

  ~File() noexcept {
    close(descriptor);
  }

};

namespace file {

const Checked<FileOpenError, File> Open(const char* filePath, int flags) noexcept {
  int fd = open(filePath, flags);
  if (fd != -1) {
    return Ok<FileOpenError, File>(File(fd, flags));
  } else {
    return Error<FileOpenError, File>(FileOpenErrorFromErrno(errno));
  }
}

const Checked<FileOpenError, File> Open(String filePath, int flags) noexcept {
  return Open(filePath.CString(), flags);
}

const Checked<FileOpenError, File> Open(const char* filePath) noexcept {
  return Open(filePath, O_RDWR);
}

const Checked<FileOpenError, File> Open(const String& filePath) noexcept {
  return Open(filePath.CString(), O_RDWR);
}

const Checked<FileOpenError, File> OpenForRead(const char* filePath) noexcept {
  return Open(filePath, O_RDONLY);
}

const Checked<FileOpenError, File> OpenForRead(const String& filePath) noexcept {
  return Open(filePath.CString(), O_RDONLY);
}

const Checked<FileOpenError, File> OpenForWrite(const char* filePath) noexcept {
  return Open(filePath, O_WRONLY);
}

const Checked<FileOpenError, File> OpenForWrite(const String& filePath) noexcept {
  return Open(filePath.CString(), O_WRONLY);
}

bool Exists(const char* filePath) noexcept {
  struct stat stats;
  return (stat(filePath, &stats)) == 0;
}

bool Exists(const String& filePath) noexcept {
  return Exists(filePath.CString());
}

}

}