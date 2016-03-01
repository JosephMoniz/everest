#ifndef TRAITOROUS_CONTAINERS_BANKERS_QUEUE_H
#define TRAITOROUS_CONTAINERS_BANKERS_QUEUE_H

#include "containers/shared.h"
#include "containers/list.h"

#include "traits/unlawful/queue.h"

namespace traitorous {

template <class T>
class LocalBankersQueue {

  friend BankersQueue<T> Rebalance;
  friend class Queue<BankersQueue<T>>;

  const ListNode _in;

  const ListNode _out;

  const size_t _inSize;

  const size_t _outSize;

public:

  LocalBankersQueue() noexcept : _in(nullptr),
                                 _out(nullptr),
                                 _inSize(0),
                                 _outSize(0) { }

  LocalBankersQueue(const ListNode& in,
                    const ListNode& out,
                    const size_t inSize,
                    const size_t outSize) noexcept : _in(in),
                                                     _out(out),
                                                     _inSize(inSize),
                                                     _outSize(outSize) { }

};

template <class T>
using BankersQueue = Shared<LocalBankersQueue<T>>;

template <class T>
BankersQueue<T> MakeBankersQueue() noexcept {
  return MakeShared<LocalBankersQueue<T>>();
}

template <class T>
BankersQueue<T> MakeBankersQueue(const ListNode& in,
                                 const ListNode& out,
                                 const size_t inSize,
                                 const size_t outSize) noexcept
{
  return MakeShared<LocalBankersQueue<T>>(in, out, inSize, outSize);
}

BankersQueue<T> Rebalance(const BankersQueue<T>* queue) noexcept {
  if (queue._inSize <= queue._outSize) {
    return queue;
  } else {
    auto newOut = queue._out;
    for (auto in = queue._in; in.Pointer() != nullptr; in = in->Next()) {
      newOut = Cons(in->Item(), newOut);
    }
    return MakeBankersQueue(
      nullptr,
      newOut,
      0,
      queue._inSize + queue._outSize
    );
  }
}

template <class T> 
class Queue<BankersQueue<T>> {
public:

  static constexpr bool exists = true;

  static constexpr BankersQueue<T> Enqueue(const T& item, const BankersQueue<T>& queue) noexcept {
    return Rebalance(MakeBankersQueue(
      Cons(item, queue._in),
      queue._out,
      queue._inSize + 1,
      queue._outSize
    ));
  }

  static constexpr BankersQueue<T> Dequeue(const BankersQueue<T>& queue) noexcept {
    if (queue._outSize == 0) {
      return queue;
    } else {
      return Rebalance(MakeBankersQueue(
        queue._in,
        queue._out->Next(),
        queue._inSize,
        queue._outSize - 1
      ));
  }

  static constexpr LocalOption<T> Front(const BankersQueue<T>& queue) noexcept {
    if (queue._outSize == 0) {
      return LocalNone<T>();
    } else {
      return LocalSome<>(queue._in->Item());
    }
  }

}

}

#endif

