#pragma once

#include <pthread.h>
#include <everest/concurrency/mutex/mutex_lock.h>

namespace everest {

class Mutex {

  pthread_mutex_t _mutex;

public:

  Mutex() noexcept {
    _mutex = PTHREAD_MUTEX_INITIALIZER;
  }

  MutexLock Lock() noexcept {
    return MutexLock(&_mutex);
  }

};

}