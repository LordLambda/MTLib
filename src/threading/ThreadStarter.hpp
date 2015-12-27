#ifndef THREADSTARTER_HPP
#define THREADSTARTER_HPP

#include "../Common.h"

class EXPORT ThreadBase {
public:
	ThreadBase() {}
	virtual ~ThreadBase() {}
	virtual bool run() = 0;
	virtual void OnShutdown() {}
#ifdef WIN32
	HANDLE THREAD_HANDLE;
#else
	pthread_t THREAD_HANDLE;
#endif
};

#endif
