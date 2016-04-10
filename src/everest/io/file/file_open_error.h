#pragma once

#include <sys/errno.h>

namespace everest {

enum class FileOpenError {
  ACCESS_ERROR,
  LOCKED_TERMINAL,
  QUOTA_EXHAUSTED,
  FILE_EXISTS,
  ADDRESS_FAULT,
  INTERUPTED,
  INVALID_FLAG,
  IO_ERROR,
  IS_DIRECTORY,
  SYMBOLIC_LINK_LOOP,
  TOO_MANY_OPEN_FILES,
  NAME_TOO_LONG,
  SYSTEM_FILE_TABLE_FULL,
  FILE_NON_EXISTANT,
  NO_SPACE_LEFT,
  PART_OF_PATH_NOT_DIRECTORY,
  NO_X_IO,
  OPERATION_NOT_SUPPORTED,
  SIZE_OVERFLOW,
  READ_ONLY_FILE,
  FILE_BEING_EXECUTED,
  BAD_FILE,
  UNKNOWN_ERROR
};

FileOpenError FileOpenErrorFromErrno(int error) {
  switch (error) {
    case EACCES:       return FileOpenError::ACCESS_ERROR;
    case EAGAIN:       return FileOpenError::LOCKED_TERMINAL;
    case EDQUOT:       return FileOpenError::QUOTA_EXHAUSTED;
    case EEXIST:       return FileOpenError::FILE_EXISTS;
    case EFAULT:       return FileOpenError::ADDRESS_FAULT;
    case EINTR:        return FileOpenError::INTERUPTED;
    case EINVAL:       return FileOpenError::INVALID_FLAG;
    case EIO:          return FileOpenError::IO_ERROR;
    case EISDIR:       return FileOpenError::IS_DIRECTORY;
    case ELOOP:        return FileOpenError::SYMBOLIC_LINK_LOOP;
    case EMFILE:       return FileOpenError::TOO_MANY_OPEN_FILES;
    case ENAMETOOLONG: return FileOpenError::NAME_TOO_LONG;
    case ENFILE:       return FileOpenError::SYSTEM_FILE_TABLE_FULL;
    case ENOENT:       return FileOpenError::FILE_NON_EXISTANT;
    case ENOSPC:       return FileOpenError::NO_SPACE_LEFT;
    case ENOTDIR:      return FileOpenError::PART_OF_PATH_NOT_DIRECTORY;
    case ENXIO:        return FileOpenError::NO_X_IO;
    case EOPNOTSUPP:   return FileOpenError::OPERATION_NOT_SUPPORTED;
    case EOVERFLOW:    return FileOpenError::SIZE_OVERFLOW;
    case EROFS:        return FileOpenError::READ_ONLY_FILE;
    case ETXTBSY:      return FileOpenError::FILE_BEING_EXECUTED;
    case EBADF:        return FileOpenError::BAD_FILE;
    default:           return FileOpenError::UNKNOWN_ERROR;
  }
}

}