#ifndef RWLOCK_HPP
#define RWLOCK_HPP

#include "Mutex.hpp"

class EXPORT RWLock {
public:
	FORCEINLINE void AcquireReadLock() {
		_lock.Acquire();
	}

	FORCEINLINE void ReleaseReadLock() {
		_lock.Release();
	}

	FORCEINLINE void AcquireWriteLock() {
		_lock.Acquire();
	}

	FORCEINLINE void ReleaseWriteLock() {
		_lock.Release();
	}

private:
	Mutex _lock;
};

#endif
