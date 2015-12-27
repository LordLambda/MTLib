#ifndef LOCKEDQUEUE_HPP
#define LOCKEDQUEUE_HPP

#include "Mutex.hpp"
#include <deque>

template<class TYPE>
class EXPORT LockedQueue {
public:
	~LockedQueue() { }

	FORCEINLINE void add(const TYPE & element) {
		mutex.Acquire();
		queue.push_back(element);
		mutex.Release();
	}

	FORCEINLINE TYPE next() {
		mutex.Acquire();
		assert(queue.size() > 0);
		TYPE t = queue.front();
		queue.pop_front();
		mutex.Release();
		return t;
	}

	FORCEINLINE size_t size() {
		mutex.Acquire();
		size_t c = queue.size();
		mutex.Release();
		return c;
	}

	FORCEINLINE TYPE get_first_element() {
		mutex.Acquire();
		TYPE t;
		if (queue.size() == 0)
			t = reinterpret_cast<TYPE>(0);
		else
			t = queue.front();
		mutex.Release();
		return t;
	}

	FORCEINLINE void pop() {
		mutex.Acquire();
		ASSERT(queue.size() > 0);
		queue.pop_front();
		mutex.Release();
	}

	FORCEINLINE void clear() {
		mutex.Acquire();
		queue.resize(0);
		mutex.Release();
	}

protected:
	std::deque<TYPE> queue;
	Mutex mutex;
};

#endif
