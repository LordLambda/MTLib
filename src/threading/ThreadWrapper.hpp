#ifndef THREADWRAPPER_HPP
#define THREADWRAPPER_HPP

// Class ThreadWrapper - A Wrapper around the threading Class
// that allows for ease of use in a Thread Manager, and creation
// of threads.

enum ThreadState {
    THREADSTATE_TERMINATE = 0,
    THREADSTATE_PAUSED	= 1,
    THREADSTATE_SLEEPING  = 2,
    THREADSTATE_BUSY	  = 3,
    THREADSTATE_AWAITING  = 4,
};

class EXPORT ThreadWrapper : public ThreadBase {
	public:
		ThreadWrapper();
		~ThreadWrapper();

		FORCEINLINE void SetThreadState(ThreadState thread_state) { threadState.SetVal(thread_state); }
		FORCEINLINE ThreadState GetThreadState()
		{
			unsigned long val = threadState.GetVal();
			return static_cast<ThreadState>(val);
		}
		int GetThreadId() { return threadId; }
		time_t GetStartTime() { return start_time; }
		virtual bool run();
		virtual void OnShutdown();

	protected:
		ThreadWrapper & operator=(ThreadWrapper & other)
		{
			this->start_time = other.start_time;
			this->threadId = other.threadId;
			this->threadState.SetVal(other.threadState.GetVal());
			return *this;
		}

		MTLib::AtomicCounter threadState;
		time_t start_time;
		int threadId;
};

#endif
