#pragma once

#include <sys/stat.h>
#include <everest/containers/checked.h>

namespace everest {
namespace file {

class Stat final {

  struct stat _stats;

  Stat() noexcept { }

public:

  static const Checked<int, Stat> Of(const char* filePath) noexcept {
    Stat stats;
    auto result = stat(filePath, &stats._stats);
    if (result == 0) {
      return Checked<int, Stat>::Ok(std::move(stats));
    } else {
      return Checked<int, Stat>::Error(std::move(result));
    }
  }

  static const Checked<int, Stat> Of(const String& filePath) noexcept {
    return Stat::Of(Pointer(filePath));
  }

  static const Checked<int, Stat> Of(const File& file) noexcept {
    Stat stats;
    auto result = fstat(file.Descriptor(), &stats._stats);
    if (result == 0) {
        return Checked<int, Stat>::Ok(std::move(stats));
    } else {
        return Checked<int, Stat>::Error(std::move(result));
    }
  }

  dev_t Device() const noexcept {
    return _stats.st_dev;
  }

  ino_t InodeNumber() const noexcept {
    return _stats.st_ino;
  }

  mode_t Mode() const noexcept {
    return _stats.st_mode;
  }

  nlink_t HardLinkCount() const noexcept {
    return _stats.st_nlink;
  }

  uid_t UserId() const noexcept {
    return _stats.st_uid;
  }

  gid_t GroupId() const noexcept {
    return _stats.st_gid;
  }

  dev_t DeviceType() const noexcept {
    return _stats.st_rdev;
  }

  off_t Size() const noexcept {
    return _stats.st_size;
  }

  off_t Blocks() const noexcept {
    return _stats.st_blocks;
  }

  long BlockSize() const noexcept {
    return _stats.st_blksize;
  }

  long Flags() const noexcept {
    return _stats.st_flags;
  }

  long Generation() const noexcept {
    return _stats.st_gen;
  }

//         struct timespec st_atimespec;  /* time of last access */
//         struct timespec st_mtimespec;  /* time of last data modification */
//         struct timespec st_ctimespec;  /* time of last file status change */

};

}
}
