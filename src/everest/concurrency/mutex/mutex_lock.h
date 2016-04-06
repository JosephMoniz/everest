#pragma once

#include <pthread.h>

namespace everest {

class MutexLock {

  pthread_mutex_t* _mutex;

public:

  MutexLock(pthread_mutex_t* mutex) noexcept : _mutex(mutex) {
    pthread_mutex_lock(mutex);
  }

  ~MutexLock() {
    pthread_mutex_unlock(_mutex);
  }

};

}