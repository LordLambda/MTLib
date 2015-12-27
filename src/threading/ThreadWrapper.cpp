#include "../Common.h"
#include "ThreadWrapper.hpp"

ThreadWrapper::ThreadWrapper() : ThreadBase() {
	threadState.SetVal(THREADSTATE_AWAITING);
	start_time  = 0;
}

ThreadWrapper::~ThreadWrapper() { }

bool ThreadWrapper::run() {
	return false;
}

void ThreadWrapper::OnShutdown() {
	SetThreadState(THREADSTATE_TERMINATE);
}
