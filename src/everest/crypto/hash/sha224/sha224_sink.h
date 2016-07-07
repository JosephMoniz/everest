#pragma once

#include <string.h>
#include <openssl/sha.h>
#include <everest/traits/unlawful/sink.h>
#include <everest/crypto/hash/sha224/sha224_digest.h>
#include <everest/traits/unlawful/funnel.h>

namespace everest {

class Sha224Sink final {

  friend class Sink<Sha224Sink>;

  SHA256_CTX _context;

public:

  Sha224Sink() noexcept {
    SHA224_Init(&_context);
  }

  Sha224Sink& PushThrough(const char* input) noexcept {
    SHA224_Update(&_context, input, strlen(input));
    return *this;
  }

  Sha224Sink& PushThrough(const String& input) noexcept {
    SHA224_Update(&_context, (const unsigned char*)Pointer(input), Length(input));
    return *this;
  }

  Sha224Sink& PushThrough(String&& input) noexcept {
    PushThrough(const_cast<const String&>(input));
    return *this;
  }

  template <class T>
  Sha224Sink& PushThrough(const Memory<T>& input) noexcept {
    SHA224_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  Sha224Sink& PushThrough(const MutableMemory<T>& input) noexcept {
    SHA224_Update(&_context, (const unsigned char*)Pointer(input), sizeof(T) * Length(input));
    return *this;
  }

  template <class T>
  Sha224Sink& PushThrough(const GrowableMemory<T>& input) noexcept {
    SHA224_Update(&_context, (const unsigned char*)Pointer(input), Capacity(input));
    return *this;
  }

  Sha224Sink& PushThrough(uint8_t number) noexcept {
    SHA224_Update(&_context, &number, sizeof(uint8_t));
    return *this;
  }

  Sha224Sink& PushThrough(uint16_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Sha224Sink& PushThrough(uint32_t number) noexcept {
    PushThrough((uint8_t)(number & 0xFF));
    PushThrough((uint8_t)((number >> 8) & 0xFF));
    PushThrough((uint8_t)((number >> 16) & 0xFF));
    PushThrough((uint8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Sha224Sink& PushThrough(uint64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Sha224Sink& PushThrough(int8_t number) noexcept {
    SHA224_Update(&_context, &number, sizeof(int8_t));
    return *this;
  }

  Sha224Sink& PushThrough(int16_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    return *this;
  }

  Sha224Sink& PushThrough(int32_t number) noexcept {
    PushThrough((int8_t)(number & 0xFF));
    PushThrough((int8_t)((number >> 8) & 0xFF));
    PushThrough((int8_t)((number >> 16) & 0xFF));
    PushThrough((int8_t)((number >> 24) & 0xFF));
    return *this;
  }

  Sha224Sink& PushThrough(int64_t number) noexcept {
    for (auto i = 0; i < 64; i += 8) {
      PushThrough((int8_t)((number >> i) & 0xFF));
    }
    return *this;
  }

  Sha224Sink& PushThrough(size_t size) noexcept {
    size_t bits = sizeof(size) * 8;
    for (size_t i = 0; i < bits; i += 8) {
      PushThrough((int8_t)((size >> i) & 0xFF));
    }
    return *this;
  }

  template <class T>
  Sha224Sink& PushThrough(T&& input) noexcept {
    Funnel<T>::PerformFunnel(input, *this);
    return *this;
  }

  Sha224Digest Hash() noexcept {
    Sha224Digest digest;
    SHA224_Final(MutablePointer(digest), &_context);
    return digest;
  }
  
};

}

#include <everest/crypto/hash/sha224/sink/sink.h>