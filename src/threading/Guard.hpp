#ifndef GUARD_HPP
#define GUARD_HPP

#include "Mutex.hpp"

/************************************************************************/
/* Guard class, unlocks mutex on destroy								*/
/************************************************************************/
// crossplatform :)

class EXPORT Guard {
public:
	Guard(Mutex*mutex) : target(mutex) {
		this->target->Acquire();
	}

	~Guard() {
		this->target->Release();
	}

	Guard & operator=(Guard & src) {
		this->target = src.target;
		return *this;
	}
protected:
	Mutex*target;
};

#endif
