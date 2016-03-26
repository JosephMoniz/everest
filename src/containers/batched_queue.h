#ifndef TRAITOROUS_CONTAINERS_BATCHED_QUEUE_H
#define TRAITOROUS_CONTAINERS_BATCHED_QUEUE_H

#include "containers/shared.h"
#include "containers/list.h"

#include "traits/unlawful/queue.h"

namespace traitorous {

template <class T>
class BatchedQueue;

template <class T>
class LocalBatchedQueue final {

  friend BatchedQueue<T> Rebalance(const BatchedQueue<T>& queue);
  friend class Queue<BatchedQueue<T>>;

  const ListNode<T> _in;

  const ListNode<T> _out;

  const size_t _inSize;

  const size_t _outSize;

  ListNode<T> In() {
    return _in;
  }

public:

  LocalBatchedQueue() noexcept : _in(nullptr),
                                 _out(nullptr),
                                 _inSize(0),
                                 _outSize(0) { }

  LocalBatchedQueue(const ListNode& in,
                    const ListNode& out,
                    const size_t inSize,
                    const size_t outSize) noexcept : _in(in),
                                                     _out(out),
                                                     _inSize(inSize),
                                                     _outSize(outSize) { }

};

template <class T>
using BatchedQueue = Shared<LocalBatchedQueue<T>>;

template <class T>
BatchedQueue<T> MakeBatchedQueue() noexcept {
  return MakeShared<LocalBatchedQueue<T>>();
}

template <class T>
BatchedQueue<T> MakeBatchedQueue(const ListNode& in,
                                 const ListNode& out,
                                 const size_t inSize,
                                 const size_t outSize) noexcept
{
  return MakeShared<LocalBatchedQueue<T>>(in, out, inSize, outSize);
}

template <class T>
BatchedQueue<T> Rebalance(const BatchedQueue<T>& queue) noexcept {
  if (queue->_inSize > 0 && queue->_outSize == 0) {
    ListNode<T> newOut = queue->_out;
    for (auto it = queue->In(); it.Pointer() != nullptr; it = it->Next()) {
      newOut = Cons(it->Item(), newOut);
    }
    return MakeBatchedQueue(
      nullptr,
      newOut,
      0,
      queue->_inSize + queue->_outSize
    );
  } else {
    return queue;
  }
}

template <class T>
class Queue<BatchedQueue<T>> {
public:

  static constexpr bool exists = true;

  static constexpr BatchedQueue<T> Enqueue(const T& item,
                                           const BatchedQueue<T>& queue) noexcept
  {
    return MakeBatchedQueue(
      Cons(item, queue->_in),
      queue->_out,
      queue->_inSize + 1,
      queue->_outSize
    );
  }

  static constexpr BatchedQueue<T> Dequeue(const BatchedQueue<T>& queue) noexcept {
    if (queue->_outSize == 0) {
      if (queue->_inSize > 0) {
        return Queue<BatchedQueue<T>>::Dequeue(Rebalance(queue));
      } else {
        return queue;
      }
    } else {
      return MakeBatchedQueue(
        queue->_in,
        queue->_out->Next(),
        queue->_inSize,
        queue->_outSize - 1
      );
    }
  }

  static constexpr LocalOption<T> Front(const BatchedQueue<T>& queue) noexcept {
    if (queue->_outSize == 0) {
      if (queue->_inSize > 0) {
        return Queue<BatchedQueue<T>>::Front(Rebalance(queue));
      } else {
        return LocalNone<T>();
      }
    } else {
      return LocalSome<>(queue->_in->Item());
    }
  }

}

}

#endif

